#pragma once

// ============================================================
// Board configuration for Macroboard BRZ (ESP32-S2-DevKitC-1)
// ============================================================

#include <Arduino.h>

// --- Button configuration ---
constexpr int NUM_BUTTONS = 12;

// Physical GPIO pins for each button (index 0..11)
constexpr int BUTTON_PINS[NUM_BUTTONS] = {41, 40, 45, 42, 39, 0, 2, 38, 35, 1, 37, 36};

// Debounce time in milliseconds
constexpr unsigned long DEBOUNCE_DELAY_MS = 5;

// --- LED configuration ---
constexpr int LED_COUNT = 12;
constexpr int LED_PIN = 34;

// Maps button index → LED index on the NeoPixel strip
constexpr int LED_MAP[NUM_BUTTONS] = {9, 10, 11, 8, 7, 6, 3, 4, 5, 2, 1, 0};

// --- Extra GPIO output pins (active on specific buttons) ---
constexpr int GPIO_BTN0 = 33;
constexpr int GPIO_BTN1 = 11;
constexpr int GPIO_BTN2 = 16;
constexpr int GPIO_BTN3 = 21;
constexpr int GPIO_BTN6 = 20;
constexpr int GPIO_BTN9 = 19;
