Navi
====

Controls the motor and sensor of the navigation display on the 2001 to 2008 Mazda 6. Replacing the stock screen controller functionality with a customizable one.

This is useful if you want to use the stock navigation enclosure with a tablet and want to retain the same buttons and functionality of the original screen.

This code can be used for controlling the RX-8 navigation screen as well. ( modify tresholds for open, closed and tilted positions)

The circuit:
* 2 pushbuttons attached from pin 2 and 3 to GND (use existing buttons on Mazda 6 input screen / RX-8 buttons)
* 1 BA6209 H-Bridge for controlling the motor with its inputs attached to pin 4 and 5.
* 1 Potentiometer to control position. (included in stock nav enclosure) conected to analog pin 0
* 1 Motor (included in stock nav enclosure)


Change Log
----------

24 October 2014
* Refactored code to remove redundant calls. 
* Split into various files to improve readability.

22 March 2014
* Initial version.


Todo
----

Update; 10/24/2014
I'm pleased to report the code has been working great so far. I've been using it for months already without running into issues.

Although, from the experience I have learned that a better circuit needs to be made to avoid wasting power. With that in mind, implementing the sleep functionality into the Arduino is my next step. In the hopes of reducing its power consumption.

Through testing I have discovered it wastes ~90mA while being powered on. It looks like nothing, but consider that the whole car uses only about ~40mA while off!!



I will provide some links, videos, and walkthroughs on how to add a tablet to your car.


Happy driving!
