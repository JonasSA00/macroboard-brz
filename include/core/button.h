#pragma once

#include "config.h"

// Initialise all button GPIO pins with internal pull-ups
void buttonsInit();

// Poll a single button, returns true if a press event was detected
bool buttonUpdate(int index);

// Returns the current toggle state for a button (true = active)
bool buttonIsActive(int index);

// Clear the active/toggle state for a button
void buttonClear(int index);

// Set the active/toggle state for a button
void buttonSetActive(int index, bool state);

// Disable button toggling (for modes that don't use toggle)
extern bool buttonToggleDisabled;
