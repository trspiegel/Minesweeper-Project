# Testing Log

Evidence that the program compiles, runs, and behaves as expected.
Screenshots are saved in the `/images` folder.

## Milestone 1 (Week 1)

| # | Test | Steps | Expected Result | Actual Result | Pass/Fail |
|---|---|---|---|---|---|
| 1 | Build | Build the solution in Visual Studio (Ctrl+Shift+B) | Build succeeds with 0 errors | | |
| 2 | Main menu | Run the program (Ctrl+F5) | Menu shows 1. New Game and 2. Quit | | |
| 3 | Letters at the menu | Type `abc` and press Enter | Error message, menu asks again, no crash | | |
| 4 | Out-of-range menu choice | Type `5` and press Enter | Error message, menu asks again | | |
| 5 | New game board | Choose 1 (New Game) | 9 x 9 board prints with row and column labels, every cell shows `#` | | |
| 6 | Reveal a cell | Enter row `3`, column `4` | The cell at row 3, column 4 changes from `#` to `.` | | |
| 7 | Reveal the same cell again | Enter row `3`, column `4` again | "That cell is already revealed" message | | |
| 8 | Out-of-range row | Enter row `12` | Error message, asks for the row again | | |
| 9 | Return to menu | Enter `0` for the row | Returns to the main menu | | |
| 10 | Quit | Choose 2 (Quit) | "Thanks for playing!" and the program exits with code 0 | | |

Screenshots:
- `images/milestone1-core-structure-build.png` (successful build)
- `images/milestone1-core-structure-run.png` (program running)
