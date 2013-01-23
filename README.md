# ULTRASONIC THEREMIN #

Author: Dan Checkoway  
Version: 1.0  
Date: January 22, 2013

<img alt="Photo 1" width="128" height="96" src="https://lh3.googleusercontent.com/-z__qlaC2LE4/UP5oyxflphI/AAAAAAAAFG8/UjlVUFarNF0/s128/IMG_2037.JPG"/>

<img alt="Photo 2" width="96" height="128" src="https://lh4.googleusercontent.com/-EWhWCNxlkJQ/UP5pacUwSzI/AAAAAAAAFHc/unhBAlgL7wg/s128/IMG_2039.JPG"/>

This gizmo is a gift I made for my nephew.  It produces light and sound that
varies as an object (i.e. your hand) moves closer or further away from the
unit.  It utilizes an ultrasonic range sensor (ping) to determine distance,
from which a corresponding frequency is calculated.  The active range is
between 2" and 18" which equates to a two octave change in pitch.  Any
distance closer or beyond that is coerced into range prior to calculating the
frequency.  The closer the distance, the higher the pitch.  There is also an
RGB LED which changes color smoothly proportionate to the distance.

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

## MODES OF OPERATION ##

In addition to the power switch (located on the side of the enclosure), there
are three slide switches which provide control over several different modes of
operation.

<img alt="Photo" width="480" height="640" src="https://lh4.googleusercontent.com/-EWhWCNxlkJQ/UP5pacUwSzI/AAAAAAAAFHc/unhBAlgL7wg/s512/IMG_2039.JPG"/>

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

## PHOTOS ##

https://picasaweb.google.com/dcheckoway/UltrasonicTheremin?authuser=0&authkey=Gv1sRgCJalsbD6rKvfEg&feat=directlink

## VIDEO / DEMO ##

http://youtu.be/1QxQKjxNeSs

## PARTS LIST ##

<pre>
Qty	Description								Part Number			Link
1	Project Box								270-1803			http://www.radioshack.com/product/index.jsp?productId=2062281
1	Ultrasonic Ranging Module				HC-SR04				http://www.hobbyking.com/hobbyking/store/__31136__Ultrasonic_Module_HC_SR04_Arduino.html
1	Speaker (parted out of old unused headphones)
1	RGB LED (common anode)										http://www.amazon.com/microtivity-IL612-Diffused-Controllable-Common/dp/B006S21SQO
1	DPDT Slide Switch						SW116-ND			http://www.digikey.com/product-detail/en/GF-126-3011/SW116-ND
1	SPDT Slide Switch						SW104-ND			http://www.digikey.com/product-detail/en/GF-624-6014/SW104-ND
2	SPST Slide Switch						SW148-ND			http://www.digikey.com/product-detail/en/GF-1123-0009/SW148-ND
1	Momentary Pushbutton					275-0646			http://www.radioshack.com/product/index.jsp?productId=2062510
1	Printed Circuit Board					276-150				http://www.radioshack.com/product/index.jsp?productId=2102845
1	Microcontroller							ATMEGA328P-PU-ND	http://www.digikey.com/product-detail/en/ATMEGA328P-PU/ATMEGA328P-PU-ND/1914589
1	28-pin IC Socket						AE10286-ND			http://www.digikey.com/product-detail/en/61303211821/AE10286-ND
10	Female/Female Jumper Wires				266					https://www.adafruit.com/products/266
1	Male header pins						S1212E-36-ND		http://www.digikey.com/product-detail/en/61303211821/S1212E-36-ND
1	9V battery connector w/4" leads			232K-ND				http://www.digikey.com/product-detail/en/61303211821/232K-ND
1	16 MHz crystal							CCR-0000001 		http://www.oddwires.com/16-000-mhz-16-mhz-crystal-hc-49-s-low-profile/
2	22 pF ceramic capacitor					CCC-0000022 		http://www.oddwires.com/22pf-50v-ceramic-disc-capacitor/
1	7805 voltage regulator					MC7805CTGOS-ND		http://www.digikey.com/product-detail/en/61303211821/MC7805CTGOS-ND
1	1N4001 diode							1N4001				http://www.oddwires.com/1n4001/
1	10 uF aluminum electrolytic capacitor	399-6100-ND			http://www.digikey.com/product-detail/en/61303211821/399-6100-ND
1	100 uF aluminum electrolytic capacitor	399-6102-ND			http://www.digikey.com/product-detail/en/61303211821/399-6102-ND
1	0.10 uF (100 nF) ceramic capacitor		CCE-0000001			http://www.oddwires.com/0-1uf-50v-ceramic-disc-capacitor/
2	10k Ohm resistor											http://www.oddwires.com/1-4w-0-25w-1-metal-film-resistor-10k-ohm-25-pack/
1	1k Ohm resistor												http://www.oddwires.com/1k-ohm-0-25w-metal-film-resistor-25-pack/
1	560 Ohm resistor						S560CACT-ND			http://www.digikey.com/product-detail/en/61303211821/S560CACT-ND
1	100 Ohm resistor											http://www.oddwires.com/100-ohm-1-4w-0-25w-1-metal-film-resistor-25-pack/
</pre>

I had a good number of the parts lying around already (resistors, capacitors,
voltage regulators, crystals, etc.), so my out of pocket cost to make this
was insignificant.  The two components which can be expensive are the
ultrasonic ranging module and the RGB LED, but I've found some uber cheap
sources for them.

Originally I bought my HC-SR04 ping sensor from Amazon Prime for $5.92, which
is probably the cheapest source (assuming you have a Prime account) all things
considered.  That price includes 2-day shipping...hard to beat.

But a week or so later, while geeking out and researching Arduino hacks for RC
stuff, I accidentally bumped into the fact that you can buy the HC-SR04 from
HobbyKing, and it's even cheaper at $2.75.  When you factor in shipping, it's
probably cheaper to go with Amazon Prime, but hey...now you have two options.

The RGB LEDs can get pretty expensive if you buy just one -- but if you want
to buy them in quantity you can drive the price way down.  I've listed a link
for a 12-pack, so it's not like you have to invest in hundreds of these
things.  You can probably think of at least 12 uses for RGB LEDs.  If not,
think harder.  Just keep in mind that if you get a clear LED (that's what I
had lying around), you probably want to diffuse it to make it less directional.
I did that on mine by just scuffing it up with a ScotchBrite pad, which worked
great.  The link I've listed is for LEDs that already come diffused.

Speaker...I was surprised by how expensive speakers can be.  You're probably
thinking I'm a serious cheapskate at this point.  Ok, maybe.  But I didn't
want to invest a ton of cash in this.  Originally I was going to use a little
piezo buzzer, but it didn't really have the oomph I was looking for.  I had a
crappy old pair of headphones lying around, and I figured maybe the speakers
in there would work for this...and they worked great.

Enclosure...this is the box I wanted to use originally:
http://www.digikey.com/product-detail/en/221I,BK/SR221-IB-ND/304246
The built-in 9V battery compartment would have kicked butt.  But that box has
screw posts in really inconvenient locations.  Serpac actually makes boards
intended for these enclosures, manufactured to fit exactly, but I had already
gotten pretty far down the line soldering this thing up on the 276-150 board.
So I caved and just got a Radio Shack enclosure.  I'm sure people who do this
more often than I do know of cheaper/better sources for enclosures.

Jumper wires...I went a little overkill, installing male header pins on the
main board, and then running female-to-female jumpers up to a connecting
board on the cover panel.  Totally unnecessary, but I wanted (a) to be able
to remove the cover panel completely (I'm not sure why, but I wanted to), and
(b) to be able to reassign connections easily in case I changed the design
(not likely, but you never know).  So you can definitely save by just wiring
directly.

Other areas where you can skimp...you don't need an IC socket for the chip
unless you plan to remove it.  So you can save a few cents soldering the chip
directly to the board.  Especially considering the fact that I put an FTDI
header on there, it makes no sense to have *both* FTDI and a removable chip.
But hey, that's how I roll.
