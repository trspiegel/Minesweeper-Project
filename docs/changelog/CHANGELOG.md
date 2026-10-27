# Changelog

Progress notes for each milestone. Newest entries are at the top.

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
