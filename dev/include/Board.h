#pragma once

#include <random>
#include <utility>
#include <vector>
#include "Cell.h"

// The game board: a grid of Cells stored as a 2D vector.
// The Board owns the grid and handles everything that involves more than one
// cell: placing mines, counting nearby mines, revealing, flagging, and printing.
class Board
{
public:
    // What happened when the player tried to reveal a cell.
    enum class RevealResult
    {
        Invalid,          // The position is off the board
        AlreadyRevealed,  // The cell was already revealed
        Flagged,          // The cell is flagged, so it can't be revealed
        Safe,             // The cell was revealed and was not a mine
        HitMine           // The cell was revealed and was a mine
    };

    // What happened when the player tried to flag or unflag a cell.
    enum class FlagResult
    {
        Invalid,          // The position is off the board
        AlreadyRevealed,  // Revealed cells can't be flagged
        Placed,           // A flag was added
        Removed           // A flag was removed
    };

    Board(int rows, int cols, int mineCount);

    int GetRows() const;
    int GetCols() const;
    int GetMineCount() const;
    int GetFlagCount() const;

    // Total mines minus flags placed. Can go below 0 if the player
    // places more flags than there are mines.
    int GetMinesRemaining() const;

    // True if (row, col) is on the board. Rows and columns start at 0.
    bool IsInBounds(int row, int col) const;

    // Reveals the cell at (row, col). Mines are placed on the first reveal,
    // so the first move is always safe. Revealing a cell with no nearby
    // mines also reveals the empty area connected to it.
    RevealResult RevealCell(int row, int col);

    // Places a flag on a hidden cell, or removes it if one is already there.
    FlagResult ToggleFlag(int row, int col);

    // True when every cell without a mine has been revealed (a win).
    bool AllSafeCellsRevealed() const;

    // Reveals every mine. Used to show the player the board after a loss.
    void RevealAllMines();

    // Prints the board with row and column labels and a symbol legend.
    void Print(bool showMines = false) const;

private:
    // Randomly places mines, keeping the first cell picked (and its neighbors,
    // when there is room) free of mines.
    void PlaceMines(int safeRow, int safeCol);

    // Returns the positions of the cells touching (row, col), including
    // diagonals. Positions past the edge of the board are left out, so a
    // corner cell has 3 neighbors, an edge cell has 5, and others have 8.
    std::vector<std::pair<int, int>> GetNeighbors(int row, int col) const;

    // Counts the mines in the cells around (row, col).
    int CountAdjacentMines(int row, int col) const;

    // Stores the nearby mine count in every cell.
    void CalculateAdjacentCounts();

    // Reveals (startRow, startCol). If it touches no mines, keeps revealing
    // outward until the whole connected empty area and its border are showing.
    void RevealEmptyArea(int startRow, int startCol);

    int m_rows;
    int m_cols;
    int m_mineCount;
    int m_flagCount;
    bool m_minesPlaced;
    std::vector<std::vector<Cell>> m_grid;
    std::mt19937 m_rng;
};
