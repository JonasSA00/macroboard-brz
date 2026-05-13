#include <Arduino.h>

#include "button.h"
#include "config.h"
#include "gpio_output.h"
#include "leds.h"

void setup() {
    Serial.begin(115200);

    buttonsInit();
    gpioOutputInit();
    ledsInit();

    randomSeed(analogRead(0));
    Serial.println("Macroboard BRZ ready.");
}

void loop() {
    for (int i = 0; i < NUM_BUTTONS; i++) {
        if (buttonUpdate(i)) {
            int ledIndex = LED_MAP[i];
            bool active = buttonIsActive(i);

            if (active) {
                ledSetRandom(ledIndex);
                gpioOutputSet(i, true);
                Serial.printf("Button %d -> LED %d ON\n", i, ledIndex);
            } else {
                ledClear(ledIndex);
                gpioOutputSet(i, false);
                Serial.printf("Button %d -> LED %d OFF\n", i, ledIndex);
            }
        }
    }
}
