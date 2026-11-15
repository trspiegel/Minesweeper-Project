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
    // showAnswers is used after a loss: hidden mines show as '*', and a flag
    // on a cell without a mine shows as 'X' so the player can see the mistake.
    char GetDisplayChar(bool showAnswers) const;

private:
    bool m_hasMine;
    bool m_isRevealed;
    bool m_isFlagged;
    int  m_adjacentMines;
};
