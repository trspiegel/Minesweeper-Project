#pragma once

class Board;

// Controls the flow of the program: the main menu and each round of play.
class Game
{
public:
    // Runs the main menu loop until the player chooses Quit.
    void Run();

private:
    // Board settings for now. Difficulty levels will replace these.
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

    // What happened during a single turn.
    enum class TurnResult
    {
        Continue,
        Won,
        Lost,
        QuitToMenu
    };

    void ShowMainMenu() const;
    void ShowHowToPlay() const;

    // Starts new rounds until the player says no to playing again.
    void PlayGames();

    // Plays one game from a fresh board until the player wins, loses, or quits.
    RoundResult PlayRound();

    // Shows the board, reads one action, and carries it out.
    TurnResult PlayTurn(Board& board);

    // Asks for a row and column. Returns false if the player cancels with 0.
    // The row and column are returned as board indexes (starting at 0).
    bool ReadMove(const Board& board, int& row, int& col) const;

    // Reveals a cell and reports whether the game was won, lost, or continues.
    TurnResult HandleReveal(Board& board, int row, int col) const;

    // Places or removes a flag and tells the player what happened.
    void HandleFlag(Board& board, int row, int col) const;

    // Prints the mine, flag, and mines-remaining counts above the board.
    void PrintStatus(const Board& board) const;

    // Asks "Play again? (Y/N)" after a win or loss.
    bool AskPlayAgain() const;
};
