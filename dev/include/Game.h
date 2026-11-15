#pragma once

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
// the difficulty the player picks.
class Game
{
public:
    Game();

    // Frees the board if one is still in memory.
    ~Game();

    // Game owns a raw Board pointer, so copying a Game would make two Games
    // delete the same Board. Copying is turned off to prevent that.
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

    // Deletes the old board (if any) and creates a new one with new.
    void CreateBoard(const Difficulty& difficulty);

    // Deletes the current board and sets the pointer back to nullptr.
    void DeleteBoard();

    // The board for the current round. nullptr when no round is being played.
    Board* m_board;
};
