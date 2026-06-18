#include <Arduino.h>

#include "config.h"

#include "core/button.h"
#include "core/gpio_output.h"
#include "core/leds.h"
#include "cruise/cruise_control.h"
#include "games/minesweeper/minesweeper.h"

enum Mode { NORMAL, GAME_SELECTION, MINESWEEPER };

static Mode currentMode = NORMAL;

void setup() {
    Serial.begin(115200);

    buttonsInit();
    gpioOutputInit();
    ledsInit();
    cruiseControlInit();

    randomSeed(analogRead(0));
    Serial.println("Macroboard BRZ ready.");
}

void loop() {
    switch (currentMode) {
        case NORMAL:
            // Clear all LEDs first
            for (int i = 0; i < LED_COUNT; i++) {
                ledClear(i);
            }
            cruiseControlUpdateLEDs();  // Update flashing LEDs
            break;
        case GAME_SELECTION:
            // Set the Minesweeper selection button LED to red
            ledSetColor(LED_MAP[0], 255, 0, 0);
            for (int i = 0; i < LED_COUNT; i++) {
                if (i != LED_MAP[0]) {
                    ledClear(i);
                }
            }
            break;
        case MINESWEEPER:
            minesweeperUpdateLEDs();
            break;
    }

    buttonToggleDisabled = (currentMode == MINESWEEPER);

    for (int i = 0; i < NUM_BUTTONS; i++) {
        if (buttonUpdate(i)) {
            bool active = buttonIsActive(i);
            int gpioPin = gpioOutputGetPin(i);

            Serial.printf("Button %d pressed - Mode %d - GPIO %s",
                          i,
                          currentMode,
                          gpioPin >= 0 ? String(gpioPin).c_str() : "none");

            switch (currentMode) {
                case NORMAL:
                    // Handle cruise control buttons
                    if (i == 0 || i == 3 || i == 6 || i == 9) {
                        cruiseControlHandleButton(i);
                    } else if (i == 11) {
                        // Enter game selection
                        currentMode = GAME_SELECTION;
                        buttonClear(i);
                        gpioOutputSet(i, false);
                        Serial.println(" -> Entered Game Selection");
                    } else {
                        // Non-cruise buttons: random colors
                        int ledIndex = LED_MAP[i];
                        if (active) {
                            ledSetRandom(ledIndex);
                        } else {
                            ledClear(ledIndex);
                        }
                    }
                    break;
                case GAME_SELECTION:
                    if (i == 0) {
                        // Select Minesweeper
                        currentMode = MINESWEEPER;
                        minesweeperInit();
                        Serial.println(" -> Started Minesweeper");
                    } else if (i == 11) {
                        // Back to normal
                        currentMode = NORMAL;
                        buttonClear(i);
                        gpioOutputSet(i, false);
                        Serial.println(" -> Back to Normal");
                    }
                    // No GPIO for game selection
                    break;
                case MINESWEEPER:
                    if (i == 11 && minesweeperIsFinished()) {
                        // Only allow exit once the game has finished
                        bool wasGameOver = minesweeperIsFinished() &&
                                           !minesweeperIsWon();  // Assuming we add isWon
                        currentMode = NORMAL;
                        buttonClear(i);
                        gpioOutputSet(i, false);
                        Serial.println(" -> Back to Normal");
                        if (wasGameOver) {
                            // No latching on lose
                        }
                    } else {
                        minesweeperHandleButton(i);
                    }
                    // No GPIO while in Minesweeper
                    break;
            }

            Serial.printf(" -> %s\n", active ? "ON" : "OFF");
        }
    }

    // GPIO outputs are momentary: HIGH only while the button is physically held.
    if (currentMode == NORMAL) {
        for (int i = 0; i < NUM_BUTTONS; i++) {
            if (gpioOutputGetPin(i) >= 0) {
                gpioOutputSet(i, buttonIsHeld(i));
            }
        }
    } else {
        for (int i = 0; i < NUM_BUTTONS; i++) {
            if (gpioOutputGetPin(i) >= 0) {
                gpioOutputSet(i, false);
            }
        }
    }
}
