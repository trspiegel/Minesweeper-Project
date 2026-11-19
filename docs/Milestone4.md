# Milestone 4: Final Version

**Project:** Console Minesweeper
**Previous milestone:** [Milestone3.md](Milestone3.md)

Week 4 was about finishing and polishing. The game was already complete and playable after Milestone 3, so this week I focused on one meaningful improvement to how the program manages objects and memory, fixed a fairness bug in the timer, added a way to reset best times, and tested the whole program from start to finish.

---

## ✅ Final Feature List

| Feature | Added in |
|---|---|
| Main menu with New Game, How to Play, Best Times, and Quit, with validated input | Milestones 1–3 |
| 2D board of `Cell` objects with row and column labels and a symbol legend | Milestone 1 |
| Random mines with a guaranteed safe first move | Milestone 2 |
| Nearby mine counts and auto-reveal of empty areas | Milestone 2 |
| Flags with a mines-remaining counter | Milestone 2 |
| Win and loss detection with play again | Milestone 2 |
| Easy (9 x 9, 10 mines), Medium (16 x 16, 40 mines), and Hard (16 x 30, 99 mines) | Milestone 3 |
| Loss screen that shows every mine, correct flags (`F`), and wrong flags (`X`) | Milestone 3 |
| Best time for each difficulty, saved to `best_times.txt` | Milestone 3 |
| **Live timer on the status line that starts on the first reveal** | **Milestone 4** |
| **Reset Best Times option with a confirmation prompt** | **Milestone 4** |

---

## ⚙️ Features Completed and Added This Week

| Feature | Issue | What it does |
|---|---|---|
| Timer starts on the first reveal | Start the timer on the first reveal and show it on the status line | The clock no longer runs while the player looks at the empty board. The status line now shows `Time: m:ss`, which stays at `0:00` until the first safe reveal. |
| Reset best times | Add a Reset Best Times option | The Best Times screen asks for (B)ack or (R)eset. Reset asks "This can't be undone. (Y/N)" before clearing the times and saving the empty list. If no times are saved, it says how to set one instead of asking. |
| Updated How to Play | — | Two new tips explain when the timer starts and how to reset best times. |

---

## 🧱 Class Structure (Final)

| Class | Responsibility |
|---|---|
| `Cell` | One square: mine, revealed, flagged, nearby count, and how it is drawn |
| `Board` | The 2D vector of `Cell` objects and every rule that involves more than one cell |
| `Game` | Menus, difficulty choice, and the flow of each round. Owns the `Board`, `ScoreManager`, and `Stopwatch` |
| `ScoreManager` | Loads, compares, saves, and clears best times using a `std::map` |
| `Stopwatch` (new) | Times a round in whole seconds with `std::chrono::steady_clock` |
| `Input` | Validated number and letter input |

`Game` only talks to the board through `Board`'s public functions, and `ScoreManager` and `Stopwatch` know nothing about the board, so each class can be changed or tested on its own.

---

## 🔧 Refactoring and Code Quality

### 1. Raw `Board*` → `std::unique_ptr<Board>` (Issue: Replace Game's raw Board pointer with std::unique_ptr)
- **Before:** `Game` held a raw `Board*`. `CreateBoard` had to call `DeleteBoard()` before `new`, `PlayGames` and the destructor had to remember to call `DeleteBoard()`, and a comment explained why copying was turned off.
- **After:** `m_board` is a `std::unique_ptr<Board>`. `CreateBoard` is one line with `std::make_unique`, and assigning the new board automatically deletes the old one. Returning to the menu calls `m_board.reset()`. `DeleteBoard()` is gone, and the destructor is `= default`.
- **Why it helped:** the compiler now guarantees the board is deleted exactly once, so a leak or a double delete is no longer possible even if I add new code paths later. This was my "meaningful improvement to objects and pointers" for the week, and it answered the question I asked in my Week 3 stand-up.
- **Something I learned:** `Game.h` only forward-declares `Board`, so the destructor still has to be declared in the header and defined in `Game.cpp`, where `Board` is a complete type. Otherwise `unique_ptr` can't generate the code to delete it.

### 2. Timing moved into its own `Stopwatch` class
- **Before:** `PlayRound` stored a `steady_clock::time_point` and did the duration math inline when the player won.
- **After:** `Stopwatch` has `Start()`, `Reset()`, `IsRunning()`, and `GetElapsedSeconds()`. `PlayRound` resets it, `HandleReveal` starts it, and `PrintStatus` and `ReportWinTime` just ask it for the seconds.
- **Why it helped:** the timing rules live in one small class, so showing the time on the status line only took one line, and `Game.cpp` no longer needs `<chrono>`.

### 3. `ScoreManager` gained `HasAnyTimes()` and `ClearAll()`
- The reset feature only needed two small functions, and all file writing still goes through the existing `Save()`, so there is still only one place that writes `best_times.txt`.

---

## 🐞 Bugs Resolved

| Bug | Cause | Fix |
|---|---|---|
| The timer counted time before the player's first move | `PlayRound` started the clock as soon as the board was printed | The `Stopwatch` starts in `HandleReveal` on the first safe reveal, like classic Minesweeper |
| Best times could only be cleared by finding and deleting `best_times.txt` by hand | No reset option existed | Added Reset Best Times with a Y/N confirmation |

All bugs and edge cases from earlier milestones were retested in the final test pass, and they still pass.

---

## 🙂 Usability Improvements
- The live timer shows players how long the round has taken while they play.
- The Best Times screen tells players how to set a first time when none are saved, instead of showing an empty list.
- Resetting asks for confirmation, because deleting saved times can't be undone.
- Every new prompt uses the same validated input as the rest of the game, so a wrong key shows the valid choices instead of crashing.

---

## ✅ Testing
- Final test pass: tests 49–67 in [testing/testing-log.md](testing/testing-log.md), covering menus, navigation, invalid input, every difficulty, the new features, and earlier tests again.
- Screenshots: `images/final-build.png`, `images/final-run.png`, and `images/final-features.png`.

## 🔮 Future Development
- Chording: reveal every unflagged neighbor of a number once the right number of flags is placed around it
- A custom board size option
- Colored numbers
- A mobile version, using what I learn in my app development courses
