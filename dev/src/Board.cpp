#include "../include/Board.h"

#include <iomanip>
#include <iostream>
#include <string>

namespace
{
    // Width of each column when the board is printed.
    // 3 characters keeps boards up to 99 columns lined up.
    const int kCellWidth = 3;
}

Board::Board(int rows, int cols)
    : m_rows(rows > 0 ? rows : 1),
      m_cols(cols > 0 ? cols : 1),
      m_grid(m_rows, std::vector<Cell>(m_cols))
{
}

int Board::GetRows() const
{
    return m_rows;
}

int Board::GetCols() const
{
    return m_cols;
}

bool Board::IsInBounds(int row, int col) const
{
    return row >= 0 && row < m_rows && col >= 0 && col < m_cols;
}

bool Board::RevealCell(int row, int col)
{
    if (!IsInBounds(row, col))
    {
        return false;
    }

    Cell& cell = m_grid[row][col];
    if (cell.IsRevealed() || cell.IsFlagged())
    {
        return false;
    }

    cell.Reveal();
    return true;
}

void Board::Print(bool showMines) const
{
    // Column numbers across the top. Players see rows and columns starting at 1.
    std::cout << "\n     ";
    for (int col = 0; col < m_cols; ++col)
    {
        std::cout << std::setw(kCellWidth) << (col + 1);
    }

    // Line under the column numbers.
    std::cout << "\n    +" << std::string(m_cols * kCellWidth, '-') << "\n";

    // One line per row: the row number, then each cell.
    for (int row = 0; row < m_rows; ++row)
    {
        std::cout << std::setw(kCellWidth) << (row + 1) << " |";
        for (int col = 0; col < m_cols; ++col)
        {
            std::cout << std::setw(kCellWidth) << m_grid[row][col].GetDisplayChar(showMines);
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
