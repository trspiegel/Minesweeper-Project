# Testing Log

Evidence that the program compiles, runs, and behaves as expected.
Screenshots are saved in the `/images` folder.

## Milestone 1 (Week 1)

| # | Test | Steps | Expected Result | Actual Result | Pass/Fail |
|---|---|---|---|---|---|
| 1 | Build | Build the solution in Visual Studio (Ctrl+Shift+B) | Build succeeds with 0 errors | Rebuild succeeded with 0 errors | Pass |
| 2 | Main menu | Run the program (Ctrl+F5) | Menu shows 1. New Game and 2. Quit | Menu showed both options | Pass |
| 3 | Letters at the menu | Type `abc` and press Enter | Error message, menu asks again, no crash | "Please enter a whole number from 1 to 2." and the menu asked again | Pass |
| 4 | Out-of-range menu choice | Type `5` and press Enter | Error message, menu asks again | Same error message, and the menu asked again | Pass |
| 5 | New game board | Choose 1 (New Game) | 9 x 9 board prints with row and column labels, every cell shows `#` | 9 x 9 board printed with labels 1-9, every cell showed `#` | Pass |
| 6 | Reveal a cell | Enter row `3`, column `4` | The cell at row 3, column 4 changes from `#` to `.` | Row 3, column 4 changed to `.` | Pass |
| 7 | Reveal the same cell again | Enter row `3`, column `4` again | "That cell is already revealed" message | "That cell is already revealed. Try another one." | Pass |
| 8 | Out-of-range row | Enter row `12` | Error message, asks for the row again | "Please enter a whole number from 0 to 9." and it asked for the row again | Pass |
| 9 | Return to menu | Enter `0` for the row | Returns to the main menu | "Returning to the main menu." and the menu appeared | Pass |
| 10 | Quit | Choose 2 (Quit) | "Thanks for playing!" and the program exits with code 0 | "Thanks for playing!" and the program exited with code 0 | Pass |

Screenshots:
- `images/milestone1-core-structure-build.png` (successful build)
- `images/milestone1-core-structure-run.png` (program running)