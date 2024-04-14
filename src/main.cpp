#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define COUNT 48
Adafruit_NeoPixel strip(COUNT, 19, NEO_GRB + NEO_KHZ800);

void setup() {
 strip.begin();
 strip.setBrightness(255);
 strip.clear();

 for (int i = 0; i < COUNT; i++)
 {
  strip.setPixelColor(i, strip.ColorHSV(0, 255, 255));
 }

 strip.show();
}

void loop() {
  for (size_t i = 0; i < 255; i+=18)
  {
    for (size_t j = 0; j < COUNT; j+=1) {
        strip.setPixelColor(j, strip.ColorHSV(0, 255, i));
    }
    strip.show();
    delay(10);
  }

  delay(1000);

    for (size_t i = 0; i < 255; i+=18)
  {
    for (size_t j = 0; j < COUNT; j+=1) {
        strip.setPixelColor(j, strip.ColorHSV(20000, 255, i));
    }
    strip.show();
    delay(10);
  }

  delay(1000);

    for (size_t i = 0; i < 255; i+=18)
  {
    for (size_t j = 0; j < COUNT; j+=1) {
        strip.setPixelColor(j, strip.ColorHSV(40000, 255, i));
    }
    strip.show();
    delay(10);
  }

  delay(1000);

  for (size_t j = 0; j < COUNT; j+=1) {
      strip.setPixelColor(j, strip.ColorHSV(0, 255, 0));
  }
  strip.show();
}
