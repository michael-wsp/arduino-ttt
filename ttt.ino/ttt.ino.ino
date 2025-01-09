#include <FastLED.h>

#define NUM_LEDS 256
#define DATA_PIN 6

CRGB leds[NUM_LEDS]

void setup() {
  // put your setup code here, to run once:
  FastLED.AddLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

}

void loop() {
  // put your main code here, to run repeatedly:

}
