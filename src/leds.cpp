#include "leds.h"

#include <Adafruit_NeoPixel.h>

static Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void ledsInit() {
    strip.begin();
    strip.setBrightness(50);
    strip.clear();
    strip.show();
}

void ledSetRandom(int ledIndex) {
    uint8_t r = random(256);
    uint8_t g = random(256);
    uint8_t b = random(256);
    strip.setPixelColor(ledIndex, strip.Color(r, g, b));
    strip.show();
}

void ledClear(int ledIndex) {
    strip.setPixelColor(ledIndex, 0);
    strip.show();
}
