#pragma once

#include "config.h"

// Initialise all extra GPIO output pins (set LOW)
void gpioOutputInit();

// Set the extra GPIO associated with a button index HIGH or LOW.
// Does nothing if the button index has no associated GPIO.
void gpioOutputSet(int buttonIndex, bool state);

// Get the GPIO pin associated with a button index (-1 if none)
int gpioOutputGetPin(int buttonIndex);
