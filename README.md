# ULTRASONIC THEREMIN #

Author: Dan Checkoway
Version: 1.0
Date: January 22, 2013

This gizmo produces light and sound that varies as an object (i.e. your hand)
moves closer or further away from the unit.  It utilizes an ultrasonic range
sensor (ping) to determine distance, from which a corresponding frequency is
calculated.  The active range is between 2" and 18" which equates to a two
octave change in pitch.  Any distance closer or beyond that is coerced into
range prior to calculating the frequency.  The closer the distance, the higher
the pitch.  There is also an RGB LED which changes color smoothly proportionate
to the distance.

## LIGHT AND SOUND EFFECTS ##

* closest   ==> red   ==> highest pitch
* mid range ==> blue  ==> one octave down
* furthest  ==> green ==> two octaves down

The code is intended for use with an RGB LED with a common anode, so the PWM
values written to the output pins are between 255 for off and 0 for on full.
If you use an LED with a common cathode, you'll simply need to remap the
values to the reverse range.

Note the forward voltage specs on your particular LED to help you determine
the appropriate resistor rating.  We rely on being able to vary the PWM output
from 0v to 5v in order to keep the code simple and therefore faster.

## SWITCHES TO CONTROL BEHAVIOR ##

* Note Mode.  Instead of allowing smooth and infinite variation in pitch,
the frequency will "snap" to the nearest semitone on the chromatic scale when
note mode is enabled.

* Key Select.  This toggles between lower and higher keys.  The low key is
"Low C" at 130.813 Hz, and the high key is "Middle C" at 261.626 Hz.  The
selected frequency is used as reference point for the lowest note, i.e. when
the object is at its maximum distance from the device.

* Continuous Mode.  Normally, sound plays through the speaker only when
the momentary pushbutton is pressed.  When continuous mode is enabled, the
button is bypassed and sound is emitted continuously.

NOTE: In pushbutton mode (non-continuous), the RGB LED will illuminate even
when the button is not pressed.  This effectively provides a silent but still
interesting mode of operation (light/color only).
