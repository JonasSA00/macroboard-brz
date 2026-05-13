#include "core/button.h"

static bool btnState[NUM_BUTTONS];
static bool lastBtnState[NUM_BUTTONS];
static bool ledToggle[NUM_BUTTONS];
static unsigned long lastDebounceTime[NUM_BUTTONS];

void buttonsInit() {
    for (int i = 0; i < NUM_BUTTONS; i++) {
        pinMode(BUTTON_PINS[i], INPUT_PULLUP);
        btnState[i]         = HIGH;
        lastBtnState[i]     = HIGH;
        ledToggle[i]        = false;
        lastDebounceTime[i] = 0;
    }
}

bool buttonUpdate(int index) {
    bool reading = digitalRead(BUTTON_PINS[index]);

    if (reading != lastBtnState[index]) {
        lastDebounceTime[index] = millis();
    }

    bool pressed = false;

    if ((millis() - lastDebounceTime[index]) > DEBOUNCE_DELAY_MS) {
        if (reading != btnState[index]) {
            btnState[index] = reading;

            if (btnState[index] == LOW) {
                // Toggle on press (if enabled)
                if (!buttonToggleDisabled) {
                    ledToggle[index] = !ledToggle[index];
                }
                pressed = true;
            }
        }
    }

    lastBtnState[index] = reading;
    return pressed;
}

bool buttonIsActive(int index) {
    return ledToggle[index];
}

void buttonClear(int index) {
    if (index < 0 || index >= NUM_BUTTONS) {
        return;
    }
    ledToggle[index] = false;
}

void buttonSetActive(int index, bool state) {
    if (index < 0 || index >= NUM_BUTTONS) {
        return;
    }
    ledToggle[index] = state;
}

bool buttonToggleDisabled = false;
