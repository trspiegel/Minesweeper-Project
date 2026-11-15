#include "../include/Game.h"
#include "../include/Board.h"
#include "../include/Input.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

namespace
{
    constexpr int kMenuNewGame = 1;
    constexpr int kMenuHowToPlay = 2;
    constexpr int kMenuBestTimes = 3;
    constexpr int kMenuQuit = 4;

    // Best times are saved here, next to the program.
    const char* const kBestTimesFile = "best_times.txt";

    // The difficulty levels, in the order they appear in the menu.
    // Sizes and mine counts match classic Minesweeper.
    const Difficulty kDifficulties[] =
    {
        { "Easy",    9,  9, 10 },
        { "Medium", 16, 16, 40 },
        { "Hard",   16, 30, 99 }
    };
    constexpr int kDifficultyCount = sizeof(kDifficulties) / sizeof(kDifficulties[0]);
}

Game::Game()
    : m_board(nullptr),
      m_scores(kBestTimesFile)
{
}

Game::~Game()
{
    DeleteBoard();
}

void Game::Run()
{
    bool running = true;
    while (running)
    {
        ShowMainMenu();
        int choice = Input::ReadInt("Choose an option: ", kMenuNewGame, kMenuQuit);

        switch (choice)
        {
        case kMenuNewGame:
            PlayGames();
            break;
        case kMenuHowToPlay:
            ShowHowToPlay();
            break;
        case kMenuBestTimes:
            ShowBestTimes();
            break;
        case kMenuQuit:
            running = false;
            break;
        }
    }

    std::cout << "\nThanks for playing!\n";
}

void Game::ShowMainMenu() const
{
    std::cout << "\n=============================\n";
    std::cout << "     CONSOLE MINESWEEPER\n";
    std::cout << "=============================\n";
    std::cout << kMenuNewGame << ". New Game\n";
    std::cout << kMenuHowToPlay << ". How to Play\n";
    std::cout << kMenuBestTimes << ". Best Times\n";
    std::cout << kMenuQuit << ". Quit\n";
}

void Game::ShowHowToPlay() const
{
    std::cout << "\n========== HOW TO PLAY ==========\n";
    std::cout << "Goal: reveal every cell that does not hide a mine.\n";
    std::cout << "Reveal a mine and the game is over.\n\n";
    std::cout << "Difficulty levels:\n";
    for (int i = 0; i < kDifficultyCount; ++i)
    {
        const Difficulty& level = kDifficulties[i];
        std::cout << "  " << level.name << ": " << level.rows << " x " << level.cols
                  << " board, " << level.mineCount << " mines\n";
    }
    std::cout << "\n";
    std::cout << "Each turn:\n";
    std::cout << "  1. Choose an action: R to reveal, F to flag or unflag,\n";
    std::cout << "     or Q to quit to the menu.\n";
    std::cout << "  2. Enter a row, then a column. Enter 0 to cancel the move.\n\n";
    std::cout << "Reading the board:\n";
    std::cout << "  #    hidden cell\n";
    std::cout << "  F    flag (a cell you think is a mine)\n";
    std::cout << "  .    no mines touch this cell\n";
    std::cout << "  1-8  how many mines touch this cell, including diagonals\n";
    std::cout << "After a loss, the board shows the answers:\n";
    std::cout << "  *    a mine\n";
    std::cout << "  F    a correct flag (it was on a mine)\n";
    std::cout << "  X    a wrong flag (it was on a safe cell)\n\n";
    std::cout << "Tips:\n";
    std::cout << "  - Your first reveal is always safe.\n";
    std::cout << "  - Revealing an empty cell opens the empty area around it.\n";
    std::cout << "  - Flagged cells can't be revealed until you unflag them.\n";
    std::cout << "  - After a game ends, you can play again or return to the menu.\n";
    std::cout << "  - Win fast to set a best time for each difficulty (see Best Times).\n";
    std::cout << "=================================\n";
}

void Game::PrintStatus(const Board& board) const
{
    std::cout << "\nMines: " << board.GetMineCount()
              << "   Flags placed: " << board.GetFlagCount()
              << "   Mines remaining: " << board.GetMinesRemaining() << "\n";
}

void Game::HandleFlag(Board& board, int row, int col) const
{
    switch (board.ToggleFlag(row, col))
    {
    case Board::FlagResult::Placed:
        std::cout << "Flag placed.\n";
        break;
    case Board::FlagResult::Removed:
        std::cout << "Flag removed.\n";
        break;
    case Board::FlagResult::AlreadyRevealed:
        std::cout << "That cell is already revealed, so it can't be flagged.\n";
        break;
    case Board::FlagResult::Invalid:
        std::cout << "That position is off the board.\n";
        break;
    }
}

bool Game::AskPlayAgain() const
{
    char answer = Input::ReadChoice("Play again? (Y/N): ", "YN");
    if (answer == 'N')
    {
        std::cout << "Returning to the main menu.\n";
    }
    return answer == 'Y';
}

bool Game::ChooseDifficulty(Difficulty& chosen) const
{
    std::cout << "\nDifficulty levels:\n";
    for (int i = 0; i < kDifficultyCount; ++i)
    {
        const Difficulty& level = kDifficulties[i];
        std::cout << (i + 1) << ". " << level.name << " (" << level.rows << " x " << level.cols
                  << ", " << level.mineCount << " mines)\n";
    }
    std::cout << "0. Back to the main menu\n";

    int choice = Input::ReadInt("Choose a difficulty: ", 0, kDifficultyCount);
    if (choice == 0)
    {
        return false;
    }
    chosen = kDifficulties[choice - 1];
    return true;
}

void Game::PlayGames()
{
    Difficulty difficulty = kDifficulties[0];
    if (!ChooseDifficulty(difficulty))
    {
        return;
    }

    // Keep starting new boards until the player says no to playing again.
    // Quitting to the menu mid-game skips the question.
    bool playAgain = true;
    while (playAgain)
    {
        RoundResult result = PlayRound(difficulty);
        playAgain = (result != RoundResult::QuitToMenu) && AskPlayAgain();
    }

    // Back at the menu, so the board isn't needed anymore.
    DeleteBoard();
}

void Game::ShowBestTimes() const
{
    std::cout << "\n========== BEST TIMES ==========\n";
    for (int i = 0; i < kDifficultyCount; ++i)
    {
        const Difficulty& level = kDifficulties[i];
        int seconds = 0;
        std::cout << "  " << std::left << std::setw(8) << level.name << std::right;
        if (m_scores.GetBestTime(level.name, seconds))
        {
            std::cout << ScoreManager::FormatTime(seconds) << "\n";
        }
        else
        {
            std::cout << "--  (not won yet)\n";
        }
    }
    std::cout << "================================\n";
}

void Game::ReportWinTime(const Difficulty& difficulty, int seconds)
{
    std::cout << "Your time: " << ScoreManager::FormatTime(seconds) << "\n";

    int oldBest = 0;
    bool hadBest = m_scores.GetBestTime(difficulty.name, oldBest);

    switch (m_scores.RecordWin(difficulty.name, seconds))
    {
    case ScoreManager::RecordResult::NewBestTime:
        std::cout << "New best time for " << difficulty.name << "!\n";
        break;
    case ScoreManager::RecordResult::NewBestTimeNotSaved:
        std::cout << "New best time for " << difficulty.name
                  << "! (It couldn't be saved to " << kBestTimesFile << ".)\n";
        break;
    case ScoreManager::RecordResult::NotABestTime:
        if (hadBest)
        {
            std::cout << "Best time for " << difficulty.name << ": "
                      << ScoreManager::FormatTime(oldBest) << "\n";
        }
        break;
    }
}

Game::RoundResult Game::PlayRound(const Difficulty& difficulty)
{
    CreateBoard(difficulty);
    std::cout << "\nNew " << difficulty.name << " game: " << m_board->GetRows() << " x "
              << m_board->GetCols() << " board with " << m_board->GetMineCount()
              << " mines. Good luck!\n";

    // The timer starts when the board is shown and stops on a win.
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    while (true)
    {
        switch (PlayTurn(*m_board))
        {
        case TurnResult::Won:
        {
            std::chrono::steady_clock::duration elapsed = std::chrono::steady_clock::now() - startTime;
            int seconds = static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(elapsed).count());
            ReportWinTime(difficulty, seconds);
            return RoundResult::Won;
        }
        case TurnResult::Lost:
            return RoundResult::Lost;
        case TurnResult::QuitToMenu:
            return RoundResult::QuitToMenu;
        case TurnResult::Continue:
            break;
        }
    }
}

Game::TurnResult Game::PlayTurn(Board& board)
{
    PrintStatus(board);
    board.Print();

    char action = Input::ReadChoice(
        "Choose an action - (R)eveal, (F)lag/unflag, or (Q)uit to menu: ", "RFQ");
    if (action == 'Q')
    {
        std::cout << "Returning to the main menu.\n";
        return TurnResult::QuitToMenu;
    }

    int row = 0;
    int col = 0;
    if (!ReadMove(board, row, col))
    {
        return TurnResult::Continue;
    }

    if (action == 'F')
    {
        HandleFlag(board, row, col);
        return TurnResult::Continue;
    }
    return HandleReveal(board, row, col);
}

bool Game::ReadMove(const Board& board, int& row, int& col) const
{
    int rows = board.GetRows();
    int cols = board.GetCols();

    int rowNumber = Input::ReadInt("Row (1-" + std::to_string(rows) + "), or 0 to cancel: ", 0, rows);
    if (rowNumber == 0)
    {
        return false;
    }
    int colNumber = Input::ReadInt("Column (1-" + std::to_string(cols) + "), or 0 to cancel: ", 0, cols);
    if (colNumber == 0)
    {
        return false;
    }

    // Players use numbers starting at 1, the board uses indexes starting at 0.
    row = rowNumber - 1;
    col = colNumber - 1;
    return true;
}

Game::TurnResult Game::HandleReveal(Board& board, int row, int col) const
{
    switch (board.RevealCell(row, col))
    {
    case Board::RevealResult::AlreadyRevealed:
        std::cout << "That cell is already revealed. Try another one.\n";
        break;
    case Board::RevealResult::Flagged:
        std::cout << "That cell is flagged. Unflag it first if you want to reveal it.\n";
        break;
    case Board::RevealResult::HitMine:
        // Show where every mine was and which flags were wrong (X).
        board.Print(true);
        std::cout << "BOOM! You hit a mine. Game over.\n";
        return TurnResult::Lost;
    case Board::RevealResult::Invalid:
        std::cout << "That position is off the board.\n";
        break;
    case Board::RevealResult::Safe:
        if (board.AllSafeCellsRevealed())
        {
            board.Print();
            std::cout << "You cleared every safe cell. You win!\n";
            return TurnResult::Won;
        }
        break;
    }
    return TurnResult::Continue;
}

void Game::CreateBoard(const Difficulty& difficulty)
{
    // Free the last round's board first so its memory isn't leaked.
    DeleteBoard();
    m_board = new Board(difficulty.rows, difficulty.cols, difficulty.mineCount);
}

void Game::DeleteBoard()
{
    // Deleting nullptr does nothing, so this is safe to call at any time.
    delete m_board;
    m_board = nullptr;
}
