# TSpiegel_Milestone2: Week 2 Changes

**Project:** Console Minesweeper
**Planning worksheet:** [TSpiegel-Milestone2-Planning.md](TSpiegel-Milestone2-Planning.md)

At the end of Week 1, the game could print a 9 x 9 board and reveal cells, but there were no mines, so it couldn't be won or lost. This week it became a complete, playable game.

---

## ⚙️ Features Added

| Feature | Issue | What it does |
|---|---|---|
| Mine placement | #6 | Places 10 mines randomly after the first reveal. The first cell and its neighbors are always safe. |
| Nearby mine counts | #7 | Each cell counts the mines in its 8 neighbors, and revealed cells show that number (1–8). |
| Auto-reveal | #8 | Revealing a cell with no nearby mines opens the whole connected empty area and the numbers around it. |
| Flags | #9 | The player can flag or unflag hidden cells. Flagged cells can't be revealed by accident. |
| Win and loss | #10 | Revealing a mine ends the game and shows every mine. Revealing every safe cell wins. |
| How to Play | New | A main menu option that explains the actions, board symbols, and tips. |
| Mines-remaining counter | New | Shows mines, flags placed, and mines remaining above the board every turn. |
| Play again | New | Asks "Play again? (Y/N)" after every win or loss. |

---

## 🧱 Code Structure Updates

No new classes were needed. Each feature went into the class that owns that responsibility:

- **Board**
  - `PlaceMines` builds a list of every allowed position, shuffles it, and uses the first 10, which gives random mines with no duplicates.
  - `CountAdjacentMines` and `CalculateAdjacentCounts` check the 8 neighbors of each cell and skip positions past the board's edges.
  - `RevealEmptyArea` uses a queue (breadth-first search) to spread the reveal outward. Each cell is revealed before it's queued, so no cell is processed twice, and the queue avoids the stack overflow risk of deep recursion.
  - `ToggleFlag`, `GetFlagCount`, and `GetMinesRemaining` handle flags.
  - `AllSafeCellsRevealed` and `RevealAllMines` handle winning and losing.
  - `RevealCell` now returns a `RevealResult` enum, and `ToggleFlag` returns a `FlagResult` enum, instead of true/false.
- **Game**
  - Added `ShowHowToPlay`, `PrintStatus`, `HandleFlag`, and `AskPlayAgain`.
  - `PlayRound` returns a `RoundResult` (Won, Lost, QuitToMenu), so `Run` knows whether to ask about playing again.
- **Input**
  - Added `ReadChoice` for validated letter input, plus shared `ReadLine` and `Trim` helpers used by both `ReadInt` and `ReadChoice`.
- **Cell**
  - No changes. It already tracked mines, flags, reveals, and nearby counts.

---

## ✨ Usability Improvements

- **How to Play screen** so a new player can learn the rules without outside help.
- **Clearer prompts:** the turn prompt names every option ("(R)eveal, (F)lag/unflag, or (Q)uit to menu"), and row and column prompts show the valid range.
- **Readable output:** a legend under the board explains every symbol, and a status line shows mines, flags placed, and mines remaining.
- **Helpful feedback:** when a move isn't allowed, the game explains why (already revealed, flagged, or off the board).
- **No dead ends:** 0 cancels a move, Q returns to the menu mid-game, and the play-again prompt follows every win or loss.

---

## 💭 What Changed and Why

| Change | Why |
|---|---|
| Mines are placed after the first reveal | Players should never lose on their very first move. |
| `RevealCell` returns an enum instead of a bool | In Week 1, the game couldn't tell why a reveal failed, so it couldn't show the right message. |
| Auto-reveal uses a queue instead of recursion | One reveal can open dozens of cells. A queue handles any size area safely and is easy to step through in the debugger. |
| Turns start with an action prompt (R/F/Q) | Using row 0 to exit only worked when revealing was the only action. With flags added, the player needs a clear way to choose what to do. |
| Mines are shuffled from a list of allowed positions | Picking random positions until one is free can repeat many times. Shuffling a list always finishes in one pass with no duplicates. |

---

## 🧪 Testing

- Tests 11–29 are recorded in [testing/testing-log.md](testing/testing-log.md).
- Screenshots: `images/milestone2-run.png` and `images/milestone2-testing.png`.
- Full notes are in [changelog/CHANGELOG.md](changelog/CHANGELOG.md).
