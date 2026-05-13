#include <Arduino.h>

#include "config.h"

#include "button.h"
#include "gpio_output.h"
#include "leds.h"
#include "cruise_control.h"

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
    cruiseControlUpdateLEDs(); // Update flashing LEDs

    for (int i = 0; i < NUM_BUTTONS; i++) {
        if (buttonUpdate(i)) {
            int ledIndex = LED_MAP[i];
            bool active  = buttonIsActive(i);
            int gpioPin = gpioOutputGetPin(i);

            Serial.printf("Button %d pressed - LED %d - GPIO %s", i, ledIndex, gpioPin >= 0 ? String(gpioPin).c_str() : "none");

            // Handle cruise control buttons
            if (i == 0 || i == 3 || i == 6 || i == 9) {
                cruiseControlHandleButton(i);
            } else {
                // Non-cruise buttons: random colors
                if (active) {
                    ledSetRandom(ledIndex);
                } else {
                    ledClear(ledIndex);
                }
            }

            gpioOutputSet(i, active);

            Serial.printf(" -> %s\n", active ? "ON" : "OFF");
        }
    }
}
