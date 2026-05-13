#pragma once

#include "config.h"

// Initialise the NeoPixel strip
void ledsInit();

// Set a specific LED to a random colour and show
void ledSetRandom(int ledIndex);

// Turn off a specific LED and show
void ledClear(int ledIndex);
