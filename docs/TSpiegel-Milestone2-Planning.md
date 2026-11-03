# TSpiegel-Milestone2-Planning

> Use this worksheet to plan the next phase of your project **before you begin coding**.
> Be clear, specific, and intentional—this will guide your development this week.

---

## 📌 Project Overview

**Project Name:**
→ Console Minesweeper

**What does your program currently do? (1–3 sentences)**
→ Console Minesweeper is a C++ console game organized into Cell, Board, Game, and Input classes, with headers in `/dev/include` and source files in `/dev/src`. Right now it shows a main menu, prints a 9 x 9 board stored as a 2D vector with row and column labels, and lets the player reveal cells by row and column. All input is validated, so letters or out-of-range numbers don't crash the program.

---

## 🔍 Current Progress Check

**What is working right now?**
→ The main menu loop (New Game and Quit), printing the board with numbered rows and columns, revealing a chosen cell, returning to the menu by entering 0, and input validation that rejects letters, extra characters, and out-of-range numbers. The project builds with no errors and was tested with 10 test cases in my testing log.

**What is NOT working or incomplete?**
→ No mines are placed yet, so every revealed cell shows as empty (`.`) and the game can't be won or lost. Nearby mine counts aren't calculated, there are no flags, revealing an empty cell doesn't open the area around it, and there are no instructions, so a new player wouldn't know the rules.

**What feels confusing or messy in your code?**
→ `Board::RevealCell` only returns true or false, so `Game` can't tell *why* a reveal failed (off the board, already revealed, or flagged) and has to guess which message to show. The turn loop in `Game::PlayRound` will also get crowded as I add flags and win/loss checks, and the row prompt currently does two jobs (choosing a row and exiting to the menu), which won't scale once there are more actions.

---

## 🚀 Feature Planning

List the features you plan to add or improve this week.

### Feature 1
**Name:**
→ Mine Placement and Nearby Mine Counts (Issues #6 and #7)

**What does this feature do?**
→ After the player's first reveal, the game randomly places 10 mines while keeping the first cell and its neighbors clear. Then every cell counts how many of its 8 neighbors hold a mine, so revealed cells show a number from 1–8 (or `.` for none).

**Why is this feature important?**
→ This is what turns the grid into an actual Minesweeper game. Without mines and numbers there is nothing to figure out, and placing mines after the first move means the player can never lose on their very first click.

---

### Feature 2
**Name:**
→ Auto-Reveal Empty Areas and Flags (Issues #8 and #9)

**What does this feature do?**
→ Revealing a cell with no nearby mines automatically opens every connected empty cell and the numbers bordering them. The player can also place or remove flags on cells they think are mines; flagged cells can't be revealed by accident, and a mines-remaining counter updates as flags are placed.

**Why is this feature important?**
→ Without auto-reveal, the player would have to reveal every empty cell one at a time, which makes the game slow and tedious. Flags are the main tool players use to keep track of where they think mines are.

---

### Feature 3 (optional)
**Name:**
→ Win/Loss Detection and Play Again (Issue #10 plus a new Issue)

**What does this feature do?**
→ Revealing a mine ends the game and shows where every mine was. Revealing every safe cell wins the game. After either result, the game asks "Play again? (Y/N)" so the player can start a new board or return to the menu.

**Why is this feature important?**
→ A game needs a clear ending. The play-again prompt also removes a dead end, since the player can start over right away instead of navigating back through the menu.

---

## 🧩 System Design Updates

**Will you need to create any new classes? If so, which ones?**
→ No new classes this week. Cell, Board, Game, and Input already split up the responsibilities well, so I'll add functions to them instead. A ScoreManager class for best times is planned for Week 3.

**Will you modify any existing classes? How?**
→
- **Board:** store the mine count and flag count; add `PlaceMines` (skips the first cell and its neighbors), `CountAdjacentMines` and `CalculateAdjacentCounts`, `RevealEmptyArea` for auto-reveal, `ToggleFlag`, `AllSafeCellsRevealed` for the win check, and `RevealAllMines` for the loss screen. `RevealCell` will return a `RevealResult` (Safe, HitMine, AlreadyRevealed, Flagged, Invalid) instead of a bool so `Game` knows exactly what happened.
- **Game:** add a How to Play screen, an action prompt (Reveal, Flag, Quit), a status line with mine and flag counts, win/loss messages, and a play-again prompt. `PlayRound` will return how the round ended (Won, Lost, or QuitToMenu).
- **Input:** add `ReadChoice` to validate letter choices like R/F/Q and Y/N.
- **Cell:** no changes needed; it already tracks mines, flags, reveals, and nearby counts.

**What data structures will you use (vectors, 2D vectors, etc.)?**
→
- A **2D vector of Cell objects** (`std::vector<std::vector<Cell>>`) for the board.
- A **vector of (row, column) pairs** that gets shuffled to pick random mine positions with no duplicates.
- A **queue of (row, column) pairs** for auto-reveal, so the reveal spreads outward one layer at a time without deep recursion.
- **Enum classes** (`RevealResult`, `FlagResult`, `RoundResult`) to report what happened clearly.

---

## 🔄 Program Flow

**Describe how a user interacts with your program:**

1. Program starts → The main menu shows 1. New Game, 2. How to Play, and 3. Quit.
2. User chooses → New Game creates a 9 x 9 board with 10 mines. Each turn, the player picks an action (R to reveal, F to flag or unflag, Q to quit to the menu), then a row and a column (0 cancels the move).
3. Program responds → The game reveals the cell (opening empty areas automatically), places or removes a flag and updates the mines-remaining counter, or explains why the move wasn't allowed. Then it reprints the board.
4. Loop/next step → Turns repeat until the player wins or hits a mine. On a loss, every mine is shown. After either result, "Play again? (Y/N)" starts a new board or returns to the main menu. Choosing Quit from the menu ends the program.

---

## 🎯 Usability Improvements

How will you make your program easier to use this week?

- Clearer prompts:
→ The turn prompt lists every option ("(R)eveal, (F)lag/unflag, or (Q)uit to menu"), the row and column prompts show the valid range, a status line shows mines, flags placed, and mines remaining, and a legend under the board explains every symbol.

- Better error handling:
→ Every input is checked. Letters, wrong letters, and out-of-range numbers show a message and ask again instead of crashing. When a move isn't allowed, the game says why (for example, "That cell is flagged. Unflag it first if you want to reveal it.").

- Improved menu/navigation:
→ Add How to Play to the main menu, let the player enter 0 to cancel a move, Q to return to the menu mid-game, and a play-again prompt after every game so there are no dead ends.

---

## ⚠️ Potential Challenges

**What do you think will be the hardest part this week?**
→ Auto-revealing empty areas. One reveal can open dozens of cells, so I need to track which cells still need to be checked, avoid revealing the same cell twice, and never read past the edges of the board. Counting nearby mines has the same edge problem at the corners and borders.

**What is your plan if you get stuck?**
→ Break the problem into smaller pieces and test each one on its own, use Visual Studio breakpoints to step through the code and watch the row, column, and queue values, and review my PG2 notes on vectors and loops. If I'm still stuck, I'll ask in the class Discord or bring it to Kari during office hours.

---

## 📈 Level Up Goal

**What skill are you focusing on improving this week?**
→ Debugging with the Visual Studio debugger (breakpoints, stepping through code, and the Watch window) instead of guessing or adding print statements.

**What will you do to improve it?**
(e.g., tutorial, practice, debugging, office hours)
→ Watch a short tutorial on the Visual Studio debugger, then practice on my own code: set a breakpoint in `RevealEmptyArea` and step through one reveal while watching the row, column, and queue, and do the same for `CountAdjacentMines` on a corner cell. I'll test each feature this way before committing it.

---

## 🗓️ Task Breakdown (GitHub Issues Planning)

List the tasks you plan to create as GitHub Issues:

- [ ] #6 Place mines randomly (first move always safe)
- [ ] #7 Count nearby mines for each cell
- [ ] #8 Reveal cells and auto-reveal empty areas
- [ ] #9 Flag and unflag cells
- [ ] #10 Check for a win or loss
- [ ] New: Add How to Play instructions to the main menu
- [ ] New: Show a mines-remaining counter above the board
- [ ] New: Ask to play again after a win or loss

---

## 🔥 Final Check

Before you start coding, ask yourself:

- [x] Do I know what I'm building this week?
- [x] Do I know where to start?
- [x] Did I break my work into small tasks?

If yes → start coding 🚀
If no → refine your plan first

---

## 😈 Final Thought

> Plan it now… or debug it later.
