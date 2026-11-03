#pragma once

class Board;

// Controls the flow of the program: the main menu and each round of play.
class Game
{
public:
    // Runs the main menu loop until the player chooses Quit.
    void Run();

private:
    // Board settings for now. Difficulty levels will set these in Week 3.
    static constexpr int kRows = 9;
    static constexpr int kCols = 9;
    static constexpr int kMineCount = 10;

    // How a round ended.
    enum class RoundResult
    {
        Won,
        Lost,
        QuitToMenu
    };

    void ShowMainMenu() const;
    void ShowHowToPlay() const;

    // Plays one game from a fresh board until the player wins, loses, or quits.
    RoundResult PlayRound();

    // Asks "Play again? (Y/N)" after a win or loss.
    bool AskPlayAgain() const;

    // Prints the mine, flag, and mines-remaining counts above the board.
    void PrintStatus(const Board& board) const;

    // Places or removes a flag and tells the player what happened.
    void HandleFlag(Board& board, int row, int col) const;
};
