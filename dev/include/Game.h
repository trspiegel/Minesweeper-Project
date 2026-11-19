#pragma once

#include "ScoreManager.h"
#include "Stopwatch.h"

#include <memory>

class Board;

// Board size and mine count for one difficulty level.
struct Difficulty
{
    const char* name;
    int rows;
    int cols;
    int mineCount;
};

// Controls the flow of the program: the main menu and each round of play.
// Game creates the Board on the heap at runtime, because its size depends on
// the difficulty the player picks. A std::unique_ptr owns the Board, so it is
// deleted automatically and can never be leaked or deleted twice.
class Game
{
public:
    Game();

    // Defined in Game.cpp, where Board is a complete type, so the unique_ptr
    // knows how to delete the Board.
    ~Game();

    // A unique_ptr can only have one owner, so a Game can't be copied.
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    // Runs the main menu loop until the player chooses Quit.
    void Run();

private:
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

    // Asks the player to pick Easy, Medium, or Hard.
    // Returns false if the player enters 0 to go back to the menu.
    bool ChooseDifficulty(Difficulty& chosen) const;

    // Asks for a difficulty, then starts new rounds at that difficulty until
    // the player says no to playing again.
    void PlayGames();

    // Plays one game on a fresh board until the player wins, loses, or quits.
    RoundResult PlayRound(const Difficulty& difficulty);

    // Prints the best time for each difficulty, or "--" if it hasn't been won.
    void ShowBestTimes() const;

    // Tells the player their winning time and whether it's a new best time.
    void ReportWinTime(const Difficulty& difficulty, int seconds);

    // Shows the board, reads one action, and carries it out.
    TurnResult PlayTurn(Board& board);

    // Asks for a row and column. Returns false if the player cancels with 0.
    // The row and column are returned as board indexes (starting at 0).
    bool ReadMove(const Board& board, int& row, int& col) const;

    // Reveals a cell and reports whether the game was won, lost, or continues.
    // The first safe reveal of a round starts the stopwatch.
    TurnResult HandleReveal(Board& board, int row, int col);

    // Places or removes a flag and tells the player what happened.
    void HandleFlag(Board& board, int row, int col) const;

    // Prints the mine, flag, mines-remaining, and time counts above the board.
    void PrintStatus(const Board& board) const;

    // Asks "Play again? (Y/N)" after a win or loss.
    bool AskPlayAgain() const;

    // Creates a new board for the chosen difficulty. The old board (if any)
    // is deleted automatically when m_board takes ownership of the new one.
    void CreateBoard(const Difficulty& difficulty);

    // The board for the current round. Empty when no round is being played.
    std::unique_ptr<Board> m_board;

    // Loads and saves the best time for each difficulty.
    ScoreManager m_scores;

    // Times the current round, starting on the first reveal.
    Stopwatch m_stopwatch;
};
