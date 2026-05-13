#pragma once

#include "config.h"

// Initialise the NeoPixel strip
void ledsInit();

// Set a specific LED to a random colour and show
void ledSetRandom(int ledIndex);

// Set a specific LED to a fixed colour and show
void ledSetColor(int ledIndex, uint8_t r, uint8_t g, uint8_t b);

// Turn off a specific LED and show
void ledClear(int ledIndex);
