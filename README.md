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
