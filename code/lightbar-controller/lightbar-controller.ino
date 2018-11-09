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
