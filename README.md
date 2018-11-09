# Neopixel Lightbar

[<img src="https://github.com/mohitbhoite/neopixel-lightbar/blob/master/images/lightbar-header.png">](https://youtu.be/xZvvPWYbvN4)

I made a neopixel lightbar controller to add color to my macro photographs. I usually just use mono colored LEDs to accomplish that, but thought something like this will give me more control.

The design uses the [Adafruit Trinket M0](https://www.adafruit.com/product/3500) as the main controller. The light bar is an [Adafruit RGBW Neopixel stick](https://www.adafruit.com/product/2868). I used four potentiometers to control intensity of each color (Red, Green, Blue, and White). By varying the individual pots, you can create a multitude of different colors.


### Parts List

 - 1 x [Adafruit Trinket M0](https://www.adafruit.com/product/3500)
 - 1 x [Adafruit RGBW Neopixel stick](https://www.adafruit.com/product/2868)
 - 4 x [Potentiometers 50K](https://www.digikey.com/product-detail/en/3310Y-001-503L/3310Y-001-503L-ND/1088222)
 - 1 x [1800mA LiPo battery](https://store.particle.io/products/li-po-battery)
 - 1 x [Slide switch](https://www.digikey.com/product-detail/en/nkk-switches/AS11CP/360-2610-ND/1051309)
 - 1 x [LiPo JST connector](https://www.adafruit.com/product/3814)

### Wiring

![Schematic](/images/lightbar-wiring.png)

### Assembly

The 3D STL files for the enclosure and the lid are under the /cad folder. They were printed on a Prusa i3 MK3 printer. 

You can secure the Neopixel strip and the Trinket M0 with small #2 wood screws.

![](/images/lightbar-assembly.png)

![](/images/lightbar-assembly-lipo.png)

The knobs should press fit onto the potentiometers.

![](/images/lightbar-knobs.png)

I used brass #2 wood screws to secure the lid on to the enclosure body.

![](/images/lightbar-top-screws.png)


### Code

Code available under the /code folder

**NOTE**: You'll need to install and add the [Adafruit Neopixel](https://github.com/adafruit/Adafruit_NeoPixel) library for this code to work. Instructions to add this in your code are available [here.](https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-installation)

```c++
#include <Adafruit_NeoPixel.h>
int red,green,blue,white = 0;

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIN 4
#define NUMPIXELS 8

//Initialize the neopixel strip
Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_RGBW + NEO_KHZ800);

void setup() {
    //Set the pins connected to the potentiometer as inputs
    pinMode(0,INPUT);
    pinMode(1,INPUT);
    pinMode(2,INPUT);
    pinMode(3,INPUT);
    
   strip.begin();
   strip.show(); // Initialize all pixels to 'off'
   rainbowCycle(1);//Flash rainbows at the begining
}

void loop() {

    //Read and store the potentiometer values
    //We are scaling them from a 12bit scale to an 8 bit scale
    red = map(analogRead(A0), 0, 4095, 0, 255);
    green = map(analogRead(A1), 0, 4095, 0, 255);
    blue = map(analogRead(A2), 0, 4095, 0, 255);
    white = map(analogRead(A3), 0, 4095, 0, 255);

    //set colors of all the eight neopixles
    for(int pixel=0;pixel<8;pixel++)
    {
        strip.setPixelColor(pixel, red, green, blue, white);
    }
    strip.show();//Update the strip with new color values
    delay(50);
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Helper function for rainbows
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
```
