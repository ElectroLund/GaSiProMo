__OsRAM intelligent display__

I’m going to get this display up and running.  It’s an intelligent LED matrix.  I might even throw in a keypad to change the patterns and such.

I’ve had this display module lying in my Big Bin of Parts for… more than 10 years.  At this point:

I’m not convinced it even works.
I don’t know what color the LEDs are (the module comes in yellow, red, and green).
And I’m certainly not convince it will be that cool, but at least it’s a project that I’ve always wanted to do.

http://www.electrolund.com/2015/10/gasipromo/


November 1

Got the display mounted to a breadboard.  How about that, it's green!
The display has a self test diagnostic mode built in, which is incredibly handy.  Saw little cute LED bits flashing and twinkling.  So the thing appears to be alive, after all these years!

Next step: wire up the Atmega Arduino.  This will be a big trek into the unknown for me. I haven't done much with Arduino yet.


http://www.electrolund.com/2015/11/day-3-arduino-setup/

November 3

I've had a bad experience with Arduino.  But perhaps I was just cranky that night.  I was also unlucky with a defective Uno.

The good news is that for my new project (which has a deadline), my new Arduino Mega is not in fact defective.  I can attest its functionality tonight, at 10:45pm.

This platform is pretty slick.  They cleverly have positioned it between full language control and  GUI-only.  The syntax is mostly C strict.  But there are abstracted functions and methods that keep the very low-level hardware constructs from mucking up the works.  In a word, Arduino has “de-engineered” the sometimes maddening experience of working in firmware on any given microcontroller.

In mere minutes, I had a PWM signal outputting a nice fade on an LED.  This would have taken me a chunk of time on the Atmel micro that is used on the board.

The IDE lacks a lot of polish, but then I suppose that’s not unintentional.  IDEs are precisely where a lot of engineers get cranky (see above), and IDEs are not the point of hardware design.

So I don’t have much to update for my project, but this little stepping stone is encouraging and enlightening.  Get it?  Englightening?


http://www.electrolund.com/2015/11/day-6-early-firmware-testing/

November 6

Things are progressing nicely.  I have the display fully wired now to the Mega.  It’s a spaghetti mess, but it’ll work.
I have the serial port on the Arduino working nicely for debug.  I also did a fair amount of thinking with regards to data and address packetizing.  It quickly became apparent that doing a bunch of digitalWrite calls for all this pins (8 data, 5 address, per character of the display) would be a nightmare.

Here is the character map for the display.

ipd2131 ASCII chart
encoded character map
So I came up with a character array method to do this.  I tested tonight with the serial port debugger to verify correct character parsing.

So far so good.


http://www.electrolund.com/2015/11/day-15-display-testing/
November 15


So I have my display working <em>sort of</em>.  It's definitely showing good old ASCII characters.  Here's a quick video of it in action:

https://youtu.be/h9ic9IhN6is

You can see <a href="https://github.com/ElectroLund/GaSiProMo/blob/master/OsRAM_Arduino/OsRAM_Arduino.ino" target="_blank">my code at GitHub</a>.

I'm quickly realizing that I will need a more sophisticated text parser to make this thing usable.  'Cuz sending a character at a time for bit-fiddling pretty much sucks.


 http://www.electrolund.com/2015/11/day-30-final-day/
November 30
I've got most of the bugs ironed out in my display interface, but not all have been squashed in the driver portion.  In other words, the method in which I can input text into the OsRAM is working nicely (I'm using a serial port console), but the nuts and bolts of how strings are sent to the display -- arguably the most important part of this project -- remains broken slightly.

The problem is that I was lazy.  I should have paid more attention to the WR and CE lines for proper data latching into the display at the right times.

Oh well, what can I say?   I got distracted.

But this challenge has been fun.  It's always fun to work under a deadline to see what you can do.  This forced me to learn more about Arduino.  And despite my first impression, I've come to see that it's pretty great.  I especially love the C++ class support.  For instance, its string and bitwise libraries are awesome.  There are things that aren't so great, like the editor.  I had consistent undo (CTRL+Z) wonkiness that scared me (I was afraid of code-eating), so I switched quickly to Notepad++ with a good syntax language profile.

Until next year.

