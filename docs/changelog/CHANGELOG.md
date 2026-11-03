# Changelog

Progress notes for each milestone. Newest entries are at the top.

## Week 2 / Milestone 2: Playable Game

### Added
- **Mine placement (#6):** 10 mines are placed randomly after the player's first reveal. The first cell and its neighbors are always kept clear, so the first move is safe and opens part of the board.
- **Nearby mine counts (#7):** every cell stores how many of its 8 neighbors hold a mine, and revealed cells show that number.
- **Auto-reveal (#8):** revealing a cell with no nearby mines opens the whole connected empty area and the numbers around it.
- **Flags (#9):** players can place and remove flags. Flagged cells can't be revealed until they're unflagged.
- **Win and loss (#10):** revealing a mine ends the game and shows every mine. Revealing every safe cell wins.
- **How to Play** option on the main menu that explains the actions, the board symbols, and tips.
- **Mines-remaining counter** above the board (mines minus flags placed).
- **Play-again prompt** after a win or loss.
- `Input::ReadChoice` for validated letter input (R/F/Q and Y/N).

### Changed
- `Board::RevealCell` now returns a `RevealResult` (Safe, HitMine, AlreadyRevealed, Flagged, Invalid) instead of true/false, so the game can show the right message for each case.
- Turns now start with an action prompt ("(R)eveal, (F)lag/unflag, or (Q)uit to menu") instead of using row 0 to exit. Entering 0 for a row or column now cancels the move.
- The board prints a legend explaining every symbol.
- `Game::PlayRound` returns how the round ended (Won, Lost, or QuitToMenu), so quitting mid-game skips the play-again question.

### Why
- Mines, counts, and auto-reveal turn the board into an actual Minesweeper game.
- The How to Play screen, clearer prompts, legend, counter, cancel option, and play-again prompt make the game easier for a new player to understand and leave no dead ends.

### Testing
- Ran tests 11–29 in `docs/testing/testing-log.md`. Screenshots are in `images/milestone2-run.png` and `images/milestone2-testing.png`.

### Next
- Difficulty levels that set the board size and mine count at runtime (#11)
- Saving best times to a file (#12)

## Week 1 / Milestone 1: Core Structure

### Added
- Private GitHub repository with `main` and `dev` branches, the course folder structure, and starter files
- GitHub Project board with an Issue for every planned feature, each with a description and a weekly Iteration
- `dev/include` (header files) and `dev/src` (source files) to keep the code organized
- `Cell` class: stores whether a cell has a mine, is revealed, or is flagged, plus its nearby mine count, and decides how the cell is drawn
- `Board` class: stores the grid as a 2D vector of Cells, checks positions, reveals cells, and prints the board with row and column labels
- `Game` class: main menu (New Game, Quit) and a turn loop where the player picks a row and column to reveal
- `Input` helper: only accepts whole numbers in a given range, so letters or bad numbers can't crash the program
- `docs/testing` for testing evidence and `docs/changelog` for progress notes

### Fixed
- My local `main` branch was still tracking `origin/master`, so every push recreated `master` on GitHub. Fixed it with `git fetch origin --prune` and `git branch -u origin/main main`.

### Known Limitations
- Mines are not placed yet, so every revealed cell shows as empty (`.`). Mine placement and nearby mine counts are planned for Week 2.

### Next
- Place mines randomly (first move always safe)
- Count nearby mines for each cell
- Reveal empty areas automatically, add flags, and check for a win or loss
