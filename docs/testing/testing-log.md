# Testing Log

Evidence that the program compiles, runs, and behaves as expected.
Screenshots are saved in the `/images` folder.

## Milestone 2 (Week 2)

| # | Test | Steps | Expected Result | Actual Result | Pass/Fail |
|---|---|---|---|---|---|
| 11 | Build | Rebuild the solution in Visual Studio | Rebuild succeeds with 0 errors | Rebuild succeeded with 0 errors | Pass |
| 12 | Main menu | Run the program (Ctrl+F5) | Menu shows 1. New Game, 2. How to Play, 3. Quit | Menu showed all three options | Pass |
| 13 | How to Play | Choose 2 | Instructions explain the actions, symbols, and tips, then the menu shows again | Instructions showed the actions, symbols, and tips, then the menu appeared | Pass |
| 14 | Safe first move | New game, then `r`, row `5`, column `5` | The first cell is never a mine, and an area of the board opens | First reveal was safe and opened an area of the board | Pass |
| 15 | Auto-reveal | Look at the board after test 14 | Every `.` cell touches only revealed cells, and the area stops at numbered cells | Empty area opened and stopped at the numbered cells around it | Pass |
| 16 | Invalid action | Type `x` at the action prompt | "Please enter R, F, or Q." and the prompt asks again | "Please enter R, F, or Q." and the prompt asked again | Pass |
| 17 | Cancel a move | Type `r`, then `0` for the row | The move is cancelled and the board prints again with no changes | Move was cancelled and the board printed again unchanged | Pass |
| 18 | Place a flag | Type `f`, then the row and column of a hidden `#` cell | `F` appears and Mines remaining goes down by 1 | `F` appeared and Mines remaining dropped from 10 to 9 | Pass |
| 19 | Reveal a flagged cell | Type `r` with the same row and column | "That cell is flagged. Unflag it first if you want to reveal it." | "That cell is flagged. Unflag it first if you want to reveal it." | Pass |
| 20 | Remove a flag | Type `f` with the same row and column | `F` disappears and Mines remaining goes back up by 1 | `F` disappeared and Mines remaining went back to 10 | Pass |
| 21 | Flag a revealed cell | Type `f` on a revealed cell | "That cell is already revealed, so it can't be flagged." | "That cell is already revealed, so it can't be flagged." | Pass |
| 22 | Nearby mine counts | Keep revealing until you hit a mine | Every mine (`*`) is shown, and each number matches the mines touching it | All mines showed as `*`, and every number matched the mines touching it | Pass |
| 23 | Loss | (Same as test 22) | "BOOM! You hit a mine. Game over." then "Play again? (Y/N)" | "BOOM! You hit a mine. Game over." then "Play again? (Y/N)" | Pass |
| 24 | Invalid play-again answer | Type `maybe` | "Please enter Y or N." and it asks again | "Please enter Y or N." and it asked again | Pass |
| 25 | Play again: yes | Type `y` | A new hidden board starts | A new hidden board started | Pass |
| 26 | Quit mid-game | Type `q` at the action prompt | Returns to the main menu with no play-again question | Returned to the main menu with no play-again question | Pass |
| 27 | Win | Reveal every safe cell (see note) | "You cleared every safe cell. You win!" then "Play again? (Y/N)" | "You cleared every safe cell. You win!" then "Play again? (Y/N)" | Pass |
| 28 | Play again: no | Type `n` | Returns to the main menu | Returned to the main menu | Pass |
| 29 | Quit | Choose 3 | "Thanks for playing!" and the program exits with code 0 | "Thanks for playing!" and the program exited with code 0 | Pass |

**Note for test 27:** If winning a full game takes too long, temporarily change `kMineCount` in `Game.h` from 10 to 1, rebuild, win the game, then change it back to 10 and rebuild before committing.

Screenshots:
- `images/milestone2-run.png` (game running with flags and the mines-remaining counter)
- `images/milestone2-testing.png` (a test result, such as the loss or win screen)

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
