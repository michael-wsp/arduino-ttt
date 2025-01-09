#include <FastLED.h>

#define NUM_LEDS 256
#define DATA_PIN 6
#define COLS 16
#define RED 0xFF4A4A
#define GREEN 0x3DFF44

CRGB leds[NUM_LEDS]

void drawX(unsigned start_x, unsigned start_y) {
  curr = start_x + start_y * COLS;
  leds[curr] = RED;
  curr += 4;
  leds[curr] = RED;
  curr += COLS - 3;
  leds[curr] = RED;
  curr += 2;
  leds[curr] = RED;
  curr += COLS - 1;
  leds[curr] = RED;
  curr += COLS - 1;
  leds[curr] = RED;
  curr += 2;
  leds[curr] = RED;
  curr += COLS - 3;
  leds[curr] = RED;
  curr += 4;
  leds[curr] = RED;
}

void drawY(unsigned start_x, unsigned start_y) {
  curr = start_x + start_y * COLS;
  leds[curr] = GREEN;
  curr += 1;
  leds[curr] = GREEN;
  curr += 1;
  leds[curr] = GREEN;
  curr += 1;
  leds[curr] = GREEN;
  curr += 1;
  leds[curr] = GREEN;
  curr += ROWS - 4;
  leds[curr] = GREEN;
  curr += 4;
  leds[curr] = GREEN;
  curr += ROWS - 4;
  leds[curr] = GREEN;
  curr += 4;
  leds[curr] = GREEN;
  curr += ROWS - 4;
  leds[curr] = GREEN;
  curr += 4;
  leds[curr] = GREEN;
  curr += ROWS - 4;
  leds[curr] = GREEN;
  curr += 1;
  leds[curr] = GREEN;
  curr += 1;
  leds[curr] = GREEN;
  curr += 1;
  leds[curr] = GREEN;
  curr += 1;
  leds[curr] = GREEN;
}

void setup() {
  // put your setup code here, to run once:
  FastLED.AddLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

}

void loop() {
  // put your main code here, to run repeatedly:

}
