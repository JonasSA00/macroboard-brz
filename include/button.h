#pragma once

#include "config.h"

// Initialise all button GPIO pins with internal pull-ups
void buttonsInit();

// Poll a single button, returns true if a press event was detected
bool buttonUpdate(int index);

// Returns the current toggle state for a button (true = active)
bool buttonIsActive(int index);
