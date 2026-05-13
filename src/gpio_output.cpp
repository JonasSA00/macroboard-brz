#include "gpio_output.h"

// Lookup table: button index → GPIO pin (-1 = no associated GPIO)
static constexpr int GPIO_LOOKUP[NUM_BUTTONS] = {
    GPIO_BTN0,  // button 0
    GPIO_BTN1,  // button 1
    GPIO_BTN2,  // button 2
    GPIO_BTN3,  // button 3
    -1,         // button 4
    -1,         // button 5
    GPIO_BTN6,  // button 6
    -1,         // button 7
    -1,         // button 8
    GPIO_BTN9,  // button 9
    -1,         // button 10
    -1,         // button 11
};

void gpioOutputInit() {
    for (int i = 0; i < NUM_BUTTONS; i++) {
        if (GPIO_LOOKUP[i] >= 0) {
            pinMode(GPIO_LOOKUP[i], OUTPUT);
            digitalWrite(GPIO_LOOKUP[i], LOW);
        }
    }
}

void gpioOutputSet(int buttonIndex, bool state) {
    if (buttonIndex < 0 || buttonIndex >= NUM_BUTTONS) {
        return;
    }
    int pin = GPIO_LOOKUP[buttonIndex];
    if (pin >= 0) {
        digitalWrite(pin, state ? HIGH : LOW);
    }
}

int gpioOutputGetPin(int buttonIndex) {
    if (buttonIndex < 0 || buttonIndex >= NUM_BUTTONS) {
        return -1;
    }
    return GPIO_LOOKUP[buttonIndex];
}
