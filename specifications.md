#Specifications

Version 0.1

###I. Hardware
####A. Components
1. The LED strip used will be a `LPD8806` 1m strip,
[bought from Adafruit](https://www.adafruit.com/products/306).
(Req I.4, II.1)
2. The power supply for the LED strip will be a 5V 2A switching power supply,
[bought from Adafruit](http://www.adafruit.com/products/276).
(Req II.2, Spec I.A.1)
3. To connect the LED strip to the TIVA board, a 4-pin JST SM plug and receptical will be used,
[bought from Adafruit](http://www.adafruit.com/products/578).
(Spec I.A.1)
4. The 4x4 matrix keypad and cables provided with the class will be used for input.
(Req III.1)

#####B. Usage
1. I/O for the matrix keypad will be connected to GPIO ports on the TIVA board.
(Req III.1, Spec I.A.4)
2. The PWM pins on the TIVA board will connect to the data / clock pins on the LED strip.
(Req I.1, I.2, Spec I.A.1)
3. The 5V power supply shall connect to the +5V pin on the LED strip.
(Req II.2, Spec I.A.1, I.A.2)

###II. Software
####A. General
1. The input from the matrix keypad will be parsed to determine which patttern was chosen.
(Req III.1)
2. A keypad button press will trigger an interrupt.
(Spec II.1)
3. All interrupts take priority over current pattern.
(Spec II.2)
4. The body of the main method will be an infinite loop, which performs the currently selected pattern.
(Req III.1)
5. The patterns will be implemented via a driver library for simplicity of programming patterns.
(Req III.1)
6. The driver library will be a rewritten version of [Adafruit's Library](https://github.com/adafruit/LPD8806)
(Spec II.A.5)
7. Commands will be passed to the LED strip via the TIVA's PWN.
(Req I.1, I.2, II.1, Spec I.A.1, I.B.2, II.A.6)

####B. Patterns
All Patterns repeat indefinitely, until a new pattern is provided.
(Req I.3)

1. Simple Chase: Sends one pixel down the line at a time, in varying colors.
2. Theatre Chase: Lights every third pixel, to create illustion of many pixels moving.
3. Ping-Pong: One pixel bounces back and forth across the strip.
4. Rainbow: The whole strip cycles through all the colors available. 
5. Rainbow Cycle: Cycles through all the colors available, varying color across the strip.
6. Even Rainbow Cycle: Cycles through all colors like rainbow, but the colors are evenly distributed.
7. Simple Chase Rainbow: A simple chase that goes through all the colors available to it.
8. Theatre Chase Rainbow: Lights every third pixel in a rainbow fashion.
9. Rainbow Pong: One pixel bounces back and forth across the strip, changing color when it touches a wall.
10. Jingle Bells: Various lights turn on to the tune of jingle bells.
11. Christmas Lights: Lights flash and light up in christmas colors.
12. Fiesta: Lights pseduo-randomly flash in warm colors.
13: Pac-Man: A simple one-dimensional demonstration of pac-man is shown.
14: TBD
15: TBD
16: No lights.
