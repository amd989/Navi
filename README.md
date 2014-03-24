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


Todo
----

In the meantime this code is a work in progress. Until I test it out completely, is not yet safe to be used (unless you want to contribute)
I will be updating the code until it replicates the stock functionality as close as possible.

I will provide some links, videos, and walkthroughs on how to add a tablet to your car.

Happy driving!
