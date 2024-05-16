# exposer
Exposure timer for PCB production, screen printing or other analog printing techniques. Quickly knocked together using parts I had laying around.

## Parts list
- Arduino Nano
- ULN2065B or similar darlington transistor array
- TM1637 4 Digit 7-Segment LED
- MT3608 boost module
- 11.5x5mm P3.0 SPDT switch
- 3x 6mm buttons
- 18650 cell with leads or 18650 holder
- UV LED stripe

## Dependency
TM1637Display library is used for driving seven-segment display.

https://github.com/avishorp/TM1637

## PCB
The board is one-sided to allow easy fabrication at home. Neagtive artwork is in PDF format. If you want to modify something like footprints of parts, the schematic and PCB layout are in KiCAD8 format. 

## Assembly
Assemble the PCB.

Tune the boost converter to LED stripe voltage.

Glue UV LED stripes on one side of plywood or something.

Glue the PCB on the other side, or use more civilized way of fixing it.

Wire the LEDs to the board. Test that everything works.

## Foldable legs
I designed this thing to be as compact and flat as possible, that's why I went with foldable legs instead of enclosure.

The design is parametric, which means, that using OpenSCAD's customizer, you can define length, thickness and angle of the legs.

Print 4 instances of each of the two STL files. Assemble each leg with a screw and a nut, or any other way like a piece of wire bent on both sides, who am I to judge. Mind the correct relative orientation of parts.

Glue or screw on the legs to the LED side of the plywood board. Now it can stand on its own above whatever you need to be exposed to UV light.

## Usage
Up and down buttons increase and decrease the exposure time.

Time is displayed in seconds or as denominator in 1/x fraction of a second.

The middle button starts the exposure.

During the exposure rounded amount of seconds left is dispayed.

## Known issues
If you connect too much LED strip, i.e. draw too much current, the voltage on the boost converter drops too much. This can lead to LEDs working inefficiently or to reboots of the arduino. The device is intended for about 10W of load.

If when using short exposures you don't release the button fast enough, it triggers consequent exposure. I added fractions of seconds just in case and never use them, that's why they are programmed ugly and stay that way.