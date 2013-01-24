/*
ULTRASONIC THEREMIN
Author: Dan Checkoway
Version: 1.0
Date: January 22, 2013

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Averager.h"

#define DEBUG 0

// Non-PWM input and output assignments.  These may use any available pin and
// were chosen for the best physical layout considering the need to wire them
// to a cover panel, for example.  We intentionally cluster the pin assignments
// to one end of the ATMEGA328P-PU chip.
#define TRIGGER_PIN 7
#define ECHO_PIN 8
#define NOTE_MODE_PIN 11
#define KEY_SELECT_PIN 12

// NOTE: These outputs require PWM.  It's well documented that the use of
// the tone() function interferes with PWM output on pins 3 and 11.  We can
// still use those pins, just not for PWM.
#define SPEAKER_PIN 10
#define RED_PIN 5
#define GREEN_PIN 6
#define BLUE_PIN 9

// The amount of time (ms) between each sample+calculate+update cycle.
#define DELAY_TIME 15

// We use an averager for smoothing.  Using raw values has the potential to
// produce a very "jumpy" response.  By adjusting the number of averaging
// samples, you effectively control the responsiveness.  The more samples,
// the slower the device responds to changes in distance, but the smoother
// the transition.
#define NUM_AVERAGING_SAMPLES 15

// This is the number by which we can divide the ping time in usec in order
// to calculate number of inches distance.  It's the speed of sound expressed
// in usec per inch divided by 2 (time out + time back).
#define PING_TO_INCHES 149.28492

// The active range is 2" to 18", and we pre-calculate min/max ping times
// to constrain the ping input to that range.  We don't care about values
// outside of that range.
#define DMIN 2
#define DMAX 18
#define PING_MIN 298
#define PING_MAX 2687

// The active distance range corresponds to two full octaves.
#define TOTAL_HALF_STEPS 24.0

// http://www.phy.mtu.edu/~suits/NoteFreqCalcs.html
#define ABASE 1.059463094359

// http://en.wikipedia.org/wiki/Piano_key_frequencies
#define MIDDLE_C 261.626
#define LOW_C 130.813

const float pi = 3.14159;
const float halfPi = 1.5708;

Averager<uint32_t> averager(NUM_AVERAGING_SAMPLES);

float r, g, b;

void setup() {
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
  
  pinMode(NOTE_MODE_PIN, INPUT);
  digitalWrite(NOTE_MODE_PIN, HIGH); // use internal pull-up
  
  pinMode(KEY_SELECT_PIN, INPUT);
  digitalWrite(KEY_SELECT_PIN, HIGH); // use internal pull-up

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Start out with solid red while we're initializing
  analogWrite(RED_PIN, 0);
  analogWrite(GREEN_PIN, 255);
  analogWrite(BLUE_PIN, 255);
  
  if (DEBUG) {
    Serial.begin(9600);
  }

  // Initialize the averager by pre-sampling
  uint16_t samples = 0;
  while (samples < NUM_AVERAGING_SAMPLES) {
    uint32_t usec = ping();
    if (usec != 0) {
      averager.integrate(constrain(usec, PING_MIN, PING_MAX));
      ++samples;
    }
    delay(10);
  }
}

void loop() {
  uint32_t usec = ping();
  if (usec != 0) {
    // Integrate the sample into our sliding average
    averager.integrate(constrain(usec, PING_MIN, PING_MAX));
  }
  
  // Technically we don't need to convert to inches, we could just use
  // PING_MIN and PING_MAX to determine where we are in the range, but
  // this one extra calculation makes debugging easier.
  float inches = averager.getAverage() / PING_TO_INCHES;
  float rangeFraction = max(0.0, (inches - DMIN) / (DMAX - DMIN));
  float numHalfSteps = max(0.0, TOTAL_HALF_STEPS * (1.0 - rangeFraction));

  // The low note in the range is determined by the key select switch,
  // which utilizes an internal pull-up resistor in the OFF position and
  // will be pulled LOW in the ON position.
  // By default we use low C.  If the switch is on, we use middle C.
  float lowNoteFreq = digitalRead(KEY_SELECT_PIN) ? LOW_C : MIDDLE_C;
  
  // Calculate the tone frequency...low note plus the number of half steps
  uint16_t freq = (uint16_t)(lowNoteFreq * pow(ABASE, numHalfSteps));
  
  // If we're in note mode, then "snap" to the nearest semitone.
  // Same deal with this switch...we use the internal pull-up resistor,
  // so it reads HIGH in the OFF position and LOW in the ON position.
  if (digitalRead(NOTE_MODE_PIN) == LOW) {
    freq = nearestNoteFrequency(freq);
  }

  // Calculate RGB based on where we are in the range
  calculateRGB(rangeFraction);

  // Update the RGB LED (common anode, so invert)
  analogWrite(RED_PIN, 255 - round(r * 255.0));
  analogWrite(GREEN_PIN, 255 - round(g * 255.0));
  analogWrite(BLUE_PIN, 255 - round(b * 255.0));
  
  // Play the tone with no fixed duration, frequency updated next cycle
  tone(SPEAKER_PIN, freq);

  if (DEBUG) {
    Serial.print(inches);
    Serial.print(" ==> ");
    Serial.print("halfSteps=");
    Serial.print(numHalfSteps);
    Serial.print(", RF=");
    Serial.print(rangeFraction);
    Serial.print(", r=");
    Serial.print(r);
    Serial.print(", g=");
    Serial.print(g);
    Serial.print(", b=");
    Serial.print(b);
    Serial.print(", freq=");
    Serial.println(freq);
  }
  
  delay(DELAY_TIME);
}

// Calculate relative values for red, green, and blue.  The supplied value
// is between 0.0 (closest) and 1.0 (furthest away).  Calculated color values
// range between 0.0 for off and 1.0 for on full.  We use simple trignometric
// functions (sine and cosine) to provide a smooth transition of colors.
// In order to "accentuate" each primary color, we give each color a
// "band" of exclusivity:
//
//    0.00 - 0.05 ==> pure red
//    0.05 - 0.48 ==> smooth transition from red to blue
//    0.48 - 0.52 ==> pure blue
//    0.52 - 0.95 ==> smooth transition from blue to green
//    0.95 - 1.00 ==> pure green
//
// NOTE: It's intentional that we transition R->B->G instead of R->G->B.
// The pink/purple hues are preferable to orange/yellow.  You can tweak this
// algorithm to suit your personal preference.
void calculateRGB(float rangeFraction) {
  if (rangeFraction <= 0.05) {
    r = 1;
    g = 0;
    b = 0;
  } else if (rangeFraction < 0.48) {
    float v = halfPi * (rangeFraction - 0.05) / 0.43;
    r = max(0, cos(v));
    g = 0;
    b = max(0, sin(v));
  } else if (rangeFraction <= 0.52) {
    r = 0;
    g = 0;
    b = 1;
  } else if (rangeFraction < 0.95) {
    float v = halfPi * (rangeFraction - 0.52) / 0.43;
    r = 0;
    g = max(0, sin(v));
    b = max(0, cos(v));
  } else {
    r = 0;
    g = 1;
    b = 0;
  }
}

// Invoke the ultrasonic ranging module to determine distance.  This returns
// a value indicating the round-trip ping time in microseconds.  Originally
// I used the NewPing library for this, but that utilized interrupts which
// interfered with tone() and/or PWM, I can't remember which (maybe both).
// I settled on this uber-simple implementation which seems to work fine.
uint32_t ping() {
  uint32_t usec;
  int attempts = 3;
  while (attempts) {
    // Ensure that the trigger pin is low before starting
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(4);
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);
    // Use a timeout here so we don't wait forever
    usec = pulseIn(ECHO_PIN, HIGH, 10000);
    // Check for zero, in case it timed out
    if (usec) {
      return usec;
    }
    // Wait a tiny bit and then try again
    delayMicroseconds(10);
    --attempts;
  }
  // No joy, just return zero, we don't want to hold up the caller
  return 0;
}

// Semitone frequencies, rounded to the nearest integer value.  These are
// used in note mode.
const uint16_t NOTES[] = {
  4186, 3951, 3729, 3520, 3322, 3136, 2960, 2794, 2637, 2489, 2349, 2217,
  2093, 1976, 1865, 1760, 1661, 1568, 1480, 1397, 1319, 1245, 1175, 1109,
  1047, 988, 932, 880, 831, 784, 740, 698, 659, 622, 587, 554,
  523, 494, 466, 440, 415, 392, 370, 349, 330, 311, 294, 277,
  261, 247, 233, 220, 208, 196, 185, 175, 165, 156, 147, 139,
  131, 123, 117, 110, 104, 98, 92, 87, 82, 78, 73, 69,
  65, 62, 58, 55, 52, 49, 46, 44, 41, 39, 37, 35,
  33, 31, 29, 28
};

// This just saves a math calculation at runtime
const uint16_t NUM_NOTES = sizeof(NOTES) / sizeof(NOTES[0]);

// Return the semitone note frequency nearest to the given arbitrary frequency.
uint16_t nearestNoteFrequency(uint16_t f) {
  uint16_t last = 9999;
  for (int k = 0; k < NUM_NOTES; ++k) {
    if (f >= NOTES[k]) {
      uint16_t dlast = last - f;
      uint16_t dthis = NOTES[k] - f;
      if (dlast > dthis || last == 9999) {
        return NOTES[k];
      } else {
        return last;
      }
    }
    last = NOTES[k];
  }
  return last;
}

