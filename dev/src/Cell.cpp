#include "../include/Cell.h"

Cell::Cell()
    : m_hasMine(false),
      m_isRevealed(false),
      m_isFlagged(false),
      m_adjacentMines(0)
{
}

bool Cell::HasMine() const
{
    return m_hasMine;
}

bool Cell::IsRevealed() const
{
    return m_isRevealed;
}

bool Cell::IsFlagged() const
{
    return m_isFlagged;
}

int Cell::GetAdjacentMines() const
{
    return m_adjacentMines;
}

void Cell::SetMine(bool hasMine)
{
    m_hasMine = hasMine;
}

void Cell::SetAdjacentMines(int count)
{
    // A cell can touch at most 8 other cells.
    if (count >= 0 && count <= 8)
    {
        m_adjacentMines = count;
    }
}

void Cell::Reveal()
{
    m_isRevealed = true;
}

void Cell::ToggleFlag()
{
    // Only hidden cells can be flagged.
    if (!m_isRevealed)
    {
        m_isFlagged = !m_isFlagged;
    }
}

char Cell::GetDisplayChar(bool showMines) const
{
    if (m_isRevealed)
    {
        if (m_hasMine)
        {
            return '*';
        }
        if (m_adjacentMines == 0)
        {
            return '.';
        }
        return static_cast<char>('0' + m_adjacentMines);
    }

    if (m_isFlagged)
    {
        return 'F';
    }
    if (showMines && m_hasMine)
    {
        return '*';
    }
    return '#';
}
