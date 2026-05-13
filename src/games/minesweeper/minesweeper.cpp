#include <Arduino.h>

#include "config.h"
#include "games/minesweeper/minesweeper.h"

#include "core/leds.h"

// 4x3 grid
#define ROWS 4
#define COLS 3
#define TOTAL_CELLS 12

enum CellState { HIDDEN, REVEALED, MINE, FLAG };

static CellState board[TOTAL_CELLS];
static bool gameOver = false;
static bool gameWon  = false;
static int mineCount = 1;  // Number of mines

// Initialize the board
void minesweeperInit() {
    // Reset board
    for (int i = 0; i < TOTAL_CELLS; i++) {
        board[i] = HIDDEN;
    }
    gameOver = false;
    gameWon  = false;

    // Place mines randomly
    int minesPlaced = 0;
    while (minesPlaced < mineCount) {
        int pos = random(TOTAL_CELLS);
        if (board[pos] != MINE) {
            board[pos] = MINE;
            minesPlaced++;
        }
    }

    Serial.println("Minesweeper started! Press buttons to reveal cells.");
    minesweeperUpdateLEDs();
}

// Handle button press
void minesweeperHandleButton(int buttonIndex) {
    if (gameOver || gameWon)
        return;

    if (board[buttonIndex] == MINE) {
        gameOver = true;
        Serial.println("Boom! Game over.");
    } else if (board[buttonIndex] == HIDDEN) {
        board[buttonIndex] = REVEALED;
        // Check win
        int revealed = 0;
        for (int i = 0; i < TOTAL_CELLS; i++) {
            if (board[i] == REVEALED)
                revealed++;
        }
        if (revealed == TOTAL_CELLS - mineCount) {
            gameWon = true;
            Serial.println("You win!");
        }
    }
    minesweeperUpdateLEDs();
}

// Update LEDs
void minesweeperUpdateLEDs() {
    if (gameWon) {
        // Win animation: flash all green
        static unsigned long lastFlash = 0;
        static bool flashOn            = false;
        if (millis() - lastFlash > 500) {
            flashOn   = !flashOn;
            lastFlash = millis();
        }
        for (int i = 0; i < TOTAL_CELLS; i++) {
            int ledIndex = LED_MAP[i];
            if (flashOn) {
                ledSetColor(ledIndex, 0, 255, 0);
            } else {
                ledClear(ledIndex);
            }
        }
    } else {
        // Normal board display
        for (int i = 0; i < TOTAL_CELLS; i++) {
            int ledIndex = LED_MAP[i];
            switch (board[i]) {
                case HIDDEN:
                    ledClear(ledIndex);
                    break;
                case REVEALED:
                    ledSetColor(ledIndex, 0, 255, 0);  // Green
                    break;
                case MINE:
                    if (gameOver) {
                        ledSetColor(ledIndex, 255, 0, 0);  // Red
                    } else {
                        ledClear(ledIndex);  // Hidden
                    }
                    break;
                case FLAG:
                    ledSetColor(ledIndex, 0, 0, 255);  // Blue
                    break;
            }
        }
    }
}

bool minesweeperIsFinished() {
    return gameOver || gameWon;
}

bool minesweeperIsWon() {
    return gameWon;
}