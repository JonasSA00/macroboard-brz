# Minesweeper Game

This folder contains the Minesweeper game implementation for the Macroboard BRZ project.

## How it works

- Button `11` enters **Game Selection** mode from normal operation.
- In Game Selection mode, button `0` starts Minesweeper.
- Once started, all button presses are used by Minesweeper.
- The game continues until you either hit a mine or reveal all safe cells.
- Button `11` only returns to normal mode once the game is finished (win or lose).

## Button layout

The button indices are arranged as follows:

```
0  1  2
3  4  5
6  7  8
9  10 11
```

## LED behavior

- Each button is mapped to a physical LED using `LED_MAP`.
- Hidden cells are turned off.
- Revealed safe cells light up **green**.
- If a mine is triggered, mine cells are shown **red**.
- When you win, all LEDs flash **green**.
- Returning to normal mode does not latch Minesweeper colors.

## Controls

- `11` in normal mode: enter game selection
- `0` in game selection: start Minesweeper
- `0-11` in Minesweeper: reveal the corresponding cell
- `11` after game end: return to normal mode

## Notes

- The game currently places `1` random mine.
- The board is 4 rows by 3 columns, matching the button arrangement.
