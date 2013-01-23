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

## DEMO VIDEO ##

<iframe width="560" height="315" src="http://www.youtube.com/embed/1QxQKjxNeSs?rel=0" frameborder="0" allowfullscreen></iframe>

## PARTS LIST ##

<pre>
Qty	Description								Part Number			Link
1	Project Box								270-1803			http://www.radioshack.com/product/index.jsp?productId=2062281
1	Ultrasonic Ranging Module				HC-SR04				http://www.amazon.com/Ultrasonic-Module-HC-SR04-Distance-Arduino/dp/B004U8TOE6
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
