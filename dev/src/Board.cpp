#include "../include/Board.h"

#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <queue>
#include <string>
#include <utility>

namespace
{
    // Width of each column when the board is printed.
    // 3 characters keeps boards up to 99 columns lined up.
    const int kCellWidth = 3;
}

Board::Board(int rows, int cols, int mineCount)
    : m_rows(rows > 0 ? rows : 1),
      m_cols(cols > 0 ? cols : 1),
      m_mineCount(0),
      m_flagCount(0),
      m_minesPlaced(false),
      m_grid(m_rows, std::vector<Cell>(m_cols)),
      m_rng(std::random_device{}())
{
    // Leave at least one safe cell so the board can always be won.
    int maxMines = m_rows * m_cols - 1;
    if (mineCount < 0)
    {
        mineCount = 0;
    }
    if (mineCount > maxMines)
    {
        mineCount = maxMines;
    }
    m_mineCount = mineCount;
}

int Board::GetRows() const
{
    return m_rows;
}

int Board::GetCols() const
{
    return m_cols;
}

int Board::GetMineCount() const
{
    return m_mineCount;
}

int Board::GetFlagCount() const
{
    return m_flagCount;
}

int Board::GetMinesRemaining() const
{
    return m_mineCount - m_flagCount;
}

bool Board::IsInBounds(int row, int col) const
{
    return row >= 0 && row < m_rows && col >= 0 && col < m_cols;
}

Board::RevealResult Board::RevealCell(int row, int col)
{
    if (!IsInBounds(row, col))
    {
        return RevealResult::Invalid;
    }

    Cell& cell = m_grid[row][col];
    if (cell.IsRevealed())
    {
        return RevealResult::AlreadyRevealed;
    }
    if (cell.IsFlagged())
    {
        return RevealResult::Flagged;
    }

    // Wait until the first reveal to place mines, so the first move is safe.
    if (!m_minesPlaced)
    {
        PlaceMines(row, col);
    }

    if (cell.HasMine())
    {
        cell.Reveal();
        return RevealResult::HitMine;
    }

    RevealEmptyArea(row, col);
    return RevealResult::Safe;
}

Board::FlagResult Board::ToggleFlag(int row, int col)
{
    if (!IsInBounds(row, col))
    {
        return FlagResult::Invalid;
    }

    Cell& cell = m_grid[row][col];
    if (cell.IsRevealed())
    {
        return FlagResult::AlreadyRevealed;
    }

    cell.ToggleFlag();
    if (cell.IsFlagged())
    {
        ++m_flagCount;
        return FlagResult::Placed;
    }

    --m_flagCount;
    return FlagResult::Removed;
}

bool Board::AllSafeCellsRevealed() const
{
    // Mines aren't placed until the first reveal, so there's nothing to win yet.
    if (!m_minesPlaced)
    {
        return false;
    }

    for (int row = 0; row < m_rows; ++row)
    {
        for (int col = 0; col < m_cols; ++col)
        {
            const Cell& cell = m_grid[row][col];
            if (!cell.HasMine() && !cell.IsRevealed())
            {
                return false;
            }
        }
    }
    return true;
}

void Board::RevealAllMines()
{
    for (int row = 0; row < m_rows; ++row)
    {
        for (int col = 0; col < m_cols; ++col)
        {
            if (m_grid[row][col].HasMine())
            {
                m_grid[row][col].Reveal();
            }
        }
    }
}

void Board::RevealEmptyArea(int startRow, int startCol)
{
    // Breadth-first search. Each revealed cell with 0 nearby mines adds its
    // hidden neighbors to the queue, so the reveal spreads outward until it
    // reaches cells that touch a mine. A queue is used instead of recursion
    // so a large empty area can't overflow the call stack, and each cell is
    // revealed before it is queued so it is never processed twice.
    std::queue<std::pair<int, int>> toCheck;
    m_grid[startRow][startCol].Reveal();
    toCheck.push(std::make_pair(startRow, startCol));

    while (!toCheck.empty())
    {
        int row = toCheck.front().first;
        int col = toCheck.front().second;
        toCheck.pop();

        // Numbered cells border a mine, so the reveal stops spreading here.
        if (m_grid[row][col].GetAdjacentMines() != 0)
        {
            continue;
        }

        for (const std::pair<int, int>& position : GetNeighbors(row, col))
        {
            Cell& neighbor = m_grid[position.first][position.second];
            if (neighbor.IsRevealed() || neighbor.IsFlagged() || neighbor.HasMine())
            {
                continue;
            }

            neighbor.Reveal();
            toCheck.push(position);
        }
    }
}

void Board::PlaceMines(int safeRow, int safeCol)
{
    // Keep the first cell and its 8 neighbors clear when there is room,
    // so the first move opens part of the board instead of a single number.
    bool keepNeighborsClear = (m_rows * m_cols - 9) >= m_mineCount;

    // Build a list of every position that is allowed to hold a mine.
    std::vector<std::pair<int, int>> candidates;
    for (int row = 0; row < m_rows; ++row)
    {
        for (int col = 0; col < m_cols; ++col)
        {
            bool isFirstCell = (row == safeRow && col == safeCol);
            bool isNeighbor = std::abs(row - safeRow) <= 1 && std::abs(col - safeCol) <= 1;
            if (isFirstCell || (keepNeighborsClear && isNeighbor))
            {
                continue;
            }
            candidates.push_back(std::make_pair(row, col));
        }
    }

    // Shuffle the list and use the first positions. This gives random mines
    // with no duplicates and no "keep guessing until it works" loop.
    std::shuffle(candidates.begin(), candidates.end(), m_rng);

    int available = static_cast<int>(candidates.size());
    int minesToPlace = (m_mineCount < available) ? m_mineCount : available;
    for (int i = 0; i < minesToPlace; ++i)
    {
        m_grid[candidates[i].first][candidates[i].second].SetMine(true);
    }

    m_mineCount = minesToPlace;
    m_minesPlaced = true;
    CalculateAdjacentCounts();
}

std::vector<std::pair<int, int>> Board::GetNeighbors(int row, int col) const
{
    std::vector<std::pair<int, int>> neighbors;
    for (int rowOffset = -1; rowOffset <= 1; ++rowOffset)
    {
        for (int colOffset = -1; colOffset <= 1; ++colOffset)
        {
            int neighborRow = row + rowOffset;
            int neighborCol = col + colOffset;

            // Skip the cell itself and anything past the edge of the board.
            if ((rowOffset == 0 && colOffset == 0) || !IsInBounds(neighborRow, neighborCol))
            {
                continue;
            }
            neighbors.push_back(std::make_pair(neighborRow, neighborCol));
        }
    }
    return neighbors;
}

int Board::CountAdjacentMines(int row, int col) const
{
    int count = 0;
    for (const std::pair<int, int>& neighbor : GetNeighbors(row, col))
    {
        if (m_grid[neighbor.first][neighbor.second].HasMine())
        {
            ++count;
        }
    }
    return count;
}

void Board::CalculateAdjacentCounts()
{
    for (int row = 0; row < m_rows; ++row)
    {
        for (int col = 0; col < m_cols; ++col)
        {
            m_grid[row][col].SetAdjacentMines(CountAdjacentMines(row, col));
        }
    }
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
    std::cout << "\nLegend:  # hidden   F flag   . empty   1-8 mines touching   * mine\n\n";
}
