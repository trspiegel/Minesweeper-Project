# Milestone 3: Week 3 Changes

**Project:** Console Minesweeper
**Previous milestone:** [TSpiegel_Milestone2.md](TSpiegel_Milestone2.md)

At the end of Week 2, the game was fully playable, but only on one fixed 9 x 9 board, and some of the code was getting long and repetitive. Week 3 focused on making the program more reliable and easier to extend: I refactored the two biggest problem areas first, then used the cleaner structure to add difficulty levels, a clearer loss screen, and saved best times.

---

## ⚙️ Features Added

| Feature | Issue | What it does |
|---|---|---|
| Difficulty levels | #11 | New Game now asks for Easy (9 x 9, 10 mines), Medium (16 x 16, 40 mines), or Hard (16 x 30, 99 mines), or 0 to go back. The board is created at runtime at that size. Play again keeps the same difficulty. |
| Best times | #12 | The game times each round and saves the fastest win for each difficulty to `best_times.txt`. A new **Best Times** option on the main menu shows them, and a win tells you your time and whether it's a new best. |
| Show wrong flags after a loss | Show incorrect flags after a loss | When you hit a mine, the board shows every mine as `*`, keeps correct flags as `F`, and marks flags on safe cells with `X`, so you can see which guesses were wrong. |
| Updated How to Play | — | Lists the three difficulty levels, explains the `*`, `F`, and `X` symbols on the loss screen, and mentions Best Times. |

---

## 🧱 System Design Updates

### Class overview

| Class | Responsibility | Week 3 changes |
|---|---|---|
| `Cell` | One square: mine, revealed, flagged, nearby count, and how it's drawn | `GetDisplayChar(showAnswers)` can now draw a wrong flag as `X` and a hidden mine as `*` |
| `Board` | The 2D vector of Cells and every rule that involves more than one cell | New `GetNeighbors` helper; `RevealAllMines` removed; `Print(showAnswers)` prints the loss view and a matching legend |
| `Game` | Menus, difficulty choice, and the flow of each round | Split into smaller functions, owns the `Board` through a pointer, and uses `ScoreManager` |
| `ScoreManager` (new) | Loads, compares, and saves best times | Stores times in a `std::map<std::string, int>` and reads/writes `best_times.txt` |
| `Input` | Validated number and letter input | No changes |

### How the classes work together
- `main` creates one `Game` and calls `Run()`.
- `Game` owns a `Board*` and a `ScoreManager`. It never touches cells directly; it asks the `Board` to reveal, flag, or print.
- `Board` owns a 2D vector of `Cell` objects and uses `GetNeighbors` whenever it needs the cells around a position.
- `ScoreManager` knows nothing about the board. `Game` gives it a difficulty name and a time in seconds, and it reports back whether that's a new best.

### Data structures
- **`std::vector<std::vector<Cell>>`** for the board grid. Its size now comes from the chosen difficulty instead of a constant.
- **`std::vector<std::pair<int, int>>`** returned by `GetNeighbors`, holding only the on-board neighbor positions.
- **`std::map<std::string, int>`** in `ScoreManager`, mapping a difficulty name to its best time in seconds.
- **`Difficulty` struct and array** (`kDifficulties`) in `Game.cpp`, so the menu, How to Play, and Best Times screens all read from one list.

### Dynamic memory (Board created at runtime)
- `Game::CreateBoard` deletes the old board, then creates the new one with `new Board(rows, cols, mines)`.
- `Game::DeleteBoard` calls `delete` and sets the pointer back to `nullptr`. It runs when the player returns to the menu and in `Game`'s destructor, so the board is always freed.
- `Game`'s copy constructor and copy assignment are deleted. If a `Game` were copied, both copies would hold the same `Board*` and both would try to delete it.

---

## 🔧 Refactoring Improvements

### 1. Duplicate neighbor loops → `Board::GetNeighbors` (Issue: Refactor duplicated neighbor loops in Board)
- **Before:** `CountAdjacentMines` and `RevealEmptyArea` each had their own nested loop over the 8 surrounding cells, with the same edge checks written twice.
- **After:** `GetNeighbors(row, col)` returns only the positions that are on the board. Both functions loop over that list instead.
- **Result:** the edge-checking logic lives in one place, so a fix can't be missed in the other copy, and both functions are shorter and easier to read.

### 2. Long `Game::PlayRound` → smaller functions (Issue: Split Game::PlayRound into smaller functions)
- **Before:** `PlayRound` printed the board, read the action, read the row and column, handled flags, handled every reveal result, and checked for a win or loss in one long loop. `Run` also contained the play-again loop.
- **After:**
  - `PlayGames` asks for the difficulty and repeats rounds until the player stops.
  - `PlayRound` creates the board, starts the timer, and loops on `PlayTurn`.
  - `PlayTurn` prints the board and reads one action.
  - `ReadMove` reads the row and column (or cancel).
  - `HandleReveal` reacts to each `RevealResult`.
  - `HandleFlag` reacts to each `FlagResult`.
  - A new `TurnResult` enum (Continue, Won, Lost, QuitToMenu) tells `PlayRound` what happened.
- **Result:** each function has one job. Adding difficulty and timing only changed `PlayGames` and `PlayRound`, without touching the move-handling code.

### 3. `RevealAllMines` removed in favor of `Print(true)`
- **Before:** after a loss, `RevealAllMines` changed every mine to "revealed" just so it would print. This also hid flags that were on mines.
- **After:** `Print(true)` shows the answers (mines, correct flags, wrong flags) without changing any cell's state.
- **Result:** printing no longer changes game data, and the loss screen shows more useful information.

### 4. File handling in its own class
- Best times could have been read and written inside `Game`, but that would mix file code with menu and round logic. `ScoreManager` keeps all file work in one class, which can be tested on its own.

---

## 💭 What Changed and Why

| Change | Why |
|---|---|
| Refactored before adding features | The duplicate loops and long `PlayRound` would have made the new features harder to add and easier to break. |
| Board created with `new` instead of a local variable | The size now depends on the player's choice at runtime. This was also my Level Up goal for practicing pointers and dynamic memory. |
| Deleted `Game`'s copy constructor and copy assignment | A class that owns a raw pointer must not be copied, or two objects would delete the same board. |
| One `kDifficulties` list | The difficulty menu, How to Play, and Best Times screens can never disagree about sizes or mine counts. |
| Bad lines in `best_times.txt` are skipped | A missing or damaged file can't crash the game or load a negative time. |
| `RecordWin` returns a `RecordResult` enum | The game can tell the player whether a time was a new best, wasn't a best, or was a best that couldn't be saved. |
| Wrong flags shown as `X` | After a loss, players can learn from their mistakes instead of only seeing where the mines were. |
| `best_times.txt` added to `.gitignore` | Each player's saved times are local data, not source code. |

---

## ✅ Testing

- Tests 30–48 are in [testing/testing-log.md](testing/testing-log.md).
- Every Week 2 test still passes after the refactoring.
- Screenshots: `images/milestone3-run.png` and `images/milestone3-features.png`.

## 🔮 Next (Week 4)
- Final testing on all three difficulties and edge cases
- Final polish of prompts and screens
- Final documentation and portfolio-ready README
