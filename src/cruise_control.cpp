#include "cruise_control.h"
#include "leds.h"

static CruiseSystemState systemState = CRUISE_SYSTEM_OFF;
static CruiseEngagedState engagedState = CRUISE_DISENGAGED;

// Flash states for feedback
static bool flashAccel = false;
static bool flashCoast = false;
static unsigned long flashStartTime = 0;
static const unsigned long FLASH_DURATION = 100; // 100ms single flash

void cruiseControlInit() {
    systemState = CRUISE_SYSTEM_OFF;
    engagedState = CRUISE_DISENGAGED;
    flashAccel = false;
    flashCoast = false;
    cruiseControlUpdateLEDs();
}

void cruiseControlHandleButton(int buttonIndex) {
    switch (buttonIndex) {
        case 0: // ON/OFF system
            if (systemState == CRUISE_SYSTEM_OFF) {
                systemState = CRUISE_SYSTEM_ON;
                engagedState = CRUISE_DISENGAGED;
            } else {
                systemState = CRUISE_SYSTEM_OFF;
                engagedState = CRUISE_DISENGAGED;
            }
            break;
        case 3: // + RES / ACCEL
            if (systemState == CRUISE_SYSTEM_ON) {
                if (engagedState == CRUISE_DISENGAGED) {
                    // RES: engage cruise
                    engagedState = CRUISE_ENGAGED;
                } else {
                    // ACCEL: increase speed (when engaged)
                    flashAccel = true;
                    flashStartTime = millis();
                    // Add speed increase logic here
                }
            }
            break;
        case 6: // - SET / COAST
            if (systemState == CRUISE_SYSTEM_ON) {
                if (engagedState == CRUISE_DISENGAGED) {
                    // SET: engage cruise
                    engagedState = CRUISE_ENGAGED;
                } else {
                    // COAST: decrease speed (when engaged)
                    flashCoast = true;
                    flashStartTime = millis();
                    // Add speed decrease logic here
                }
            }
            break;
        case 9: // Cancel
            if (systemState == CRUISE_SYSTEM_ON && engagedState == CRUISE_ENGAGED) {
                engagedState = CRUISE_DISENGAGED;
                // Cruise system stays ON, just disengaged
            }
            break;
    }
    cruiseControlUpdateLEDs();
}

void cruiseControlUpdateLEDs() {
    unsigned long currentTime = millis();

    // Check if flash duration expired
    if (flashAccel && (currentTime - flashStartTime) > FLASH_DURATION) {
        flashAccel = false;
    }
    if (flashCoast && (currentTime - flashStartTime) > FLASH_DURATION) {
        flashCoast = false;
    }

    if (systemState == CRUISE_SYSTEM_OFF) {
        // System OFF: all LEDs off
        ledClear(9); // Button 0
        ledClear(8); // Button 3
        ledClear(3); // Button 6
        ledClear(2); // Button 9
    } else {
        // System ON
        ledSetColor(9, 100, 255, 150); // Button 0: pastel green (system on)

        if (engagedState == CRUISE_DISENGAGED) {
            // Not engaged: show available actions
            ledSetColor(8, 80, 150, 255); // Button 3: pastel blue (RES available)
            ledSetColor(3, 255, 255, 150); // Button 6: pastel yellow (SET available)
            ledClear(2); // Button 9: off (cancel not available)
        } else {
            // Engaged: show active controls
            // Button 3: ACCEL
            if (flashAccel) {
                ledSetColor(8, 255, 255, 255); // White flash
            } else {
                ledSetColor(8, 150, 200, 255); // Pastel blue
            }

            // Button 6: COAST
            if (flashCoast) {
                ledSetColor(3, 255, 255, 255); // White flash
            } else {
                ledSetColor(3, 255, 255, 150); // Pastel yellow
            }

            ledSetColor(2, 255, 150, 150); // Button 9: pastel red (CANCEL available)
        }
    }
}

CruiseSystemState cruiseControlGetSystemState() {
    return systemState;
}

CruiseEngagedState cruiseControlGetEngagedState() {
    return engagedState;
}