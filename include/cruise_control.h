#pragma once

#include "config.h"

// Cruise control states
enum CruiseSystemState {
    CRUISE_SYSTEM_OFF,
    CRUISE_SYSTEM_ON
};

enum CruiseEngagedState {
    CRUISE_DISENGAGED,
    CRUISE_ENGAGED
};

// Initialize cruise control
void cruiseControlInit();

// Handle button press for cruise control (called on press event)
void cruiseControlHandleButton(int buttonIndex);

// Update LED colors based on cruise state
void cruiseControlUpdateLEDs();

// Get current states
CruiseSystemState cruiseControlGetSystemState();
CruiseEngagedState cruiseControlGetEngagedState();