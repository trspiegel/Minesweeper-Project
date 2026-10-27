#pragma once

#include <vector>
#include "Cell.h"

// The game board: a grid of Cells stored as a 2D vector.
// The Board is responsible for the grid as a whole: checking positions,
// revealing cells, and printing the board to the console.
class Board
{
public:
    Board(int rows, int cols);

    int GetRows() const;
    int GetCols() const;

    // True if (row, col) is on the board. Rows and columns start at 0.
    bool IsInBounds(int row, int col) const;

    // Reveals the cell at (row, col).
    // Returns false if the position is off the board, or the cell is
    // already revealed or flagged.
    bool RevealCell(int row, int col);

    // Prints the board with row and column labels.
    void Print(bool showMines = false) const;

private:
    int m_rows;
    int m_cols;
    std::vector<std::vector<Cell>> m_grid;
};
