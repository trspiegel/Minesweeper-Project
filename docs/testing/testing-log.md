# Testing Log

Evidence that the program compiles, runs, and behaves as expected.
Screenshots are saved in the `/images` folder.

## Milestone 3 (Week 3)

| # | Test | Steps | Expected Result | Actual Result | Pass/Fail |
|---|---|---|---|---|---|
| 30 | Build | Rebuild the solution in Visual Studio | Rebuild succeeds with 0 errors | Rebuild succeeded with 0 errors | Pass |
| 31 | Main menu | Run the program (Ctrl+F5) | Menu shows 1. New Game, 2. How to Play, 3. Best Times, 4. Quit | Menu showed all four options | Pass |
| 32 | How to Play | Choose 2 | Lists Easy, Medium, and Hard with their sizes and mines, and explains `*`, `F`, and `X` on the loss screen | Showed all three difficulty levels and the loss-screen symbols | Pass |
| 33 | Difficulty menu | Choose 1 (New Game) | Shows 1. Easy, 2. Medium, 3. Hard, and 0. Back to the main menu | Showed all three levels and the back option | Pass |
| 34 | Invalid difficulty | Type `5` | "Please enter a whole number from 0 to 3." and it asks again | "Please enter a whole number from 0 to 3." and it asked again | Pass |
| 35 | Back to menu | Type `0` at the difficulty prompt | Returns to the main menu | Returned to the main menu | Pass |
| 36 | Easy board | Choose Easy | "New Easy game: 9 x 9 board with 10 mines." and a 9 x 9 board | 9 x 9 board with Mines: 10 | Pass |
| 37 | Medium board | Choose Medium | 16 x 16 board, Mines: 40 | 16 x 16 board with Mines: 40 | Pass |
| 38 | Hard board | Choose Hard, then reveal row `8`, column `30` | 16 x 30 board, Mines: 99, columns labeled 1–30, and column 30 is accepted | 16 x 30 board printed with columns 1–30, and column 30 was accepted | Pass |
| 39 | Play again keeps difficulty | Finish a Medium game, then type `y` | A new Medium board starts without asking for the difficulty again | A new 16 x 16 board with 40 mines started | Pass |
| 40 | Wrong flag after a loss | Flag a few hidden cells, then reveal cells until you hit a mine | Flags on safe cells show `X`, flags on mines stay `F`, and every other mine shows `*` | Wrong flags showed `X`, correct flags stayed `F`, and the other mines showed `*` | Pass |
| 41 | Loss legend | Look at the legend under the board from test 40 | Legend includes "F correct flag" and "X wrong flag" | Legend showed "F correct flag" and "X wrong flag" | Pass |
| 42 | No best times yet | With no `best_times.txt`, choose 3 (Best Times) | Easy, Medium, and Hard each show "-- (not won yet)" | All three showed "-- (not won yet)" | Pass |
| 43 | First win | Win an Easy game (see note) | "Your time: m:ss" and "New best time for Easy!" | Showed my time and "New best time for Easy!" | Pass |
| 44 | Best time saved | Quit, run the program again, choose Best Times | Easy shows the time from test 43 | Easy showed the same time after restarting | Pass |
| 45 | Slower win | Win Easy again, taking longer than before | Shows your time and "Best time for Easy:" with the old time, and the saved time doesn't change | Showed "Best time for Easy:" with the old time, and the saved time didn't change | Pass |
| 46 | Damaged best times file | Add a line like `garbage` to `dev/best_times.txt`, then run and open Best Times | The game starts normally, skips the bad line, and still shows the saved times | The game started normally and Easy still showed the saved time | Pass |
| 47 | Week 2 features still work | Repeat tests 16–21 and 26 on Easy | Same results as Milestone 2 | Invalid action, cancel, flag, unflag, and quit mid-game all worked the same as Milestone 2 | Pass |
| 48 | Quit | Choose 4 | "Thanks for playing!" and the program exits with code 0 | "Thanks for playing!" and the program exited with code 0 | Pass |

**Note for tests 43–45:** Winning a full game takes a while, so for these tests I temporarily changed Easy's mine count in `kDifficulties` (in `Game.cpp`) from 10 to 0 and rebuilt. With no mines, the first reveal clears the board. I waited about 10 seconds before the first reveal for test 43 and longer for test 45. After testing, I changed it back to 10, rebuilt, and deleted `dev/best_times.txt` so real best times start fresh.

Screenshots:
- `images/milestone3-run.png` (a Hard game in progress)
- `images/milestone3-features.png` (the Best Times screen or a loss screen with wrong flags)

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
