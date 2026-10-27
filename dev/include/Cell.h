#pragma once

// One square on the Minesweeper board.
// A Cell only knows about itself: whether it has a mine, whether the player
// has revealed or flagged it, and how many mines are touching it.
class Cell
{
public:
    Cell();

    bool HasMine() const;
    bool IsRevealed() const;
    bool IsFlagged() const;
    int  GetAdjacentMines() const;

    void SetMine(bool hasMine);
    void SetAdjacentMines(int count);
    void Reveal();
    void ToggleFlag();

    // Returns the character used to draw this cell in the console.
    // showMines is a debug option that shows hidden mines as '*'.
    char GetDisplayChar(bool showMines) const;

private:
    bool m_hasMine;
    bool m_isRevealed;
    bool m_isFlagged;
    int  m_adjacentMines;
};
