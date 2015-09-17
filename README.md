# twally
Rhymes with "tally." Display a tally of streaming tweets on an LED sign.

You tell the script where the Arduino board is located and what terms you want to listen for; the script uses Twitter's streaming API to listen for tweets using those terms and keeps a count; every half-second the script tells the Arduino (via serial connection) what the current count is; the Arduino prints this count to the LED sign.

## Requirements
* Arduino Uno (probably works with some other boards)
* [Adafruit 16x32 RGB LED matrix](http://www.adafruit.com/product/420) (could be easily modified to work with their [32x32 RGB matrix](http://www.adafruit.com/products/607) or other signs)
* Power source (e.g. wall wart) for LED matrix, along with jumper wires and possibly a breadboard
* Ruby: [twitter](https://github.com/sferik/twitter) and [rubyserial](https://github.com/hybridgroup/rubyserial) gems ([twitter must be v5.14](https://github.com/sferik/twitter/issues/709)). I'm running ruby 2.2.
* Arduino C: Adafruit_GFX and RGBmatrixPanel libraries

After cloning the repo, run:
`gem install twitter -v 5.14` and 
`gem install rubyserial` .
The Arduino libraries can be installed from within the Arduino IDE (v1.6.2+) in Sketch > Include Library > Manage Libraries.

Rename `credentials_template.yml` to `credentials.yml` and put your twitter keys in there.

## Arduino Wiring
[See here](https://learn.adafruit.com/32x16-32x32-rgb-led-matrix/) for how to power and wire the LED matrix. You'll need to have a separate power suppy for the matrix itself. As far as pins go, the guide should steer you exactly right; I've based the display code in this project on their examples. 

Once you've got everything wired, you'll plug in the matrix power, plug in the Arduino to a laptop or Pi via USB-B, upload the sketch from the IDE, then start the script with the appropriate parameters.

## Usage
`ruby twally.rb ARDUINO_LOCATION SEARCH_TERM [SEARCH_TERM2...]`

e.g.: `ruby twally.rb COM4 friday`
or `ruby twally.rb /dev/ttyUSB1 "dunder mifflin" #paperproducts`

Ctrl-C (or ⌘-C) to stop the script while it's running. However, restarting it (without pressing the Arduino's reset button) will both start the count over and do funky things to the numbers on the display. To reset the display to zero, press the physical reset button on the Arduino.
