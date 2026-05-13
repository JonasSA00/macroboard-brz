#pragma once

#include "config.h"

// Initialize Minesweeper game
void minesweeperInit();

// Handle button press in Minesweeper mode
void minesweeperHandleButton(int buttonIndex);

// Returns true when the current Minesweeper game is finished
bool minesweeperIsFinished();

// Returns true if the game was won
bool minesweeperIsWon();

// Update LEDs for Minesweeper
void minesweeperUpdateLEDs();