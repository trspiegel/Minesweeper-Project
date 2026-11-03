#include "../include/Game.h"
#include "../include/Board.h"
#include "../include/Input.h"

#include <iostream>
#include <string>

namespace
{
    constexpr int kMenuNewGame = 1;
    constexpr int kMenuHowToPlay = 2;
    constexpr int kMenuQuit = 3;
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
        {
            // Keep starting new boards until the player says no to playing
            // again. Quitting to the menu mid-game skips the question.
            bool playAgain = true;
            while (playAgain)
            {
                RoundResult result = PlayRound();
                playAgain = (result != RoundResult::QuitToMenu) && AskPlayAgain();
            }
            break;
        }
        case kMenuHowToPlay:
            ShowHowToPlay();
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
    std::cout << kMenuQuit << ". Quit\n";
}

void Game::ShowHowToPlay() const
{
    std::cout << "\n========== HOW TO PLAY ==========\n";
    std::cout << "Goal: reveal every cell that does not hide a mine.\n";
    std::cout << "Reveal a mine and the game is over.\n\n";
    std::cout << "Each turn:\n";
    std::cout << "  1. Choose an action: R to reveal, F to flag or unflag,\n";
    std::cout << "     or Q to quit to the menu.\n";
    std::cout << "  2. Enter a row, then a column. Enter 0 to cancel the move.\n\n";
    std::cout << "Reading the board:\n";
    std::cout << "  #    hidden cell\n";
    std::cout << "  F    flag (a cell you think is a mine)\n";
    std::cout << "  .    no mines touch this cell\n";
    std::cout << "  1-8  how many mines touch this cell, including diagonals\n\n";
    std::cout << "Tips:\n";
    std::cout << "  - Your first reveal is always safe.\n";
    std::cout << "  - Revealing an empty cell opens the empty area around it.\n";
    std::cout << "  - Flagged cells can't be revealed until you unflag them.\n";
    std::cout << "  - After a game ends, you can play again or return to the menu.\n";
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

Game::RoundResult Game::PlayRound()
{
    Board board(kRows, kCols, kMineCount);
    std::cout << "\nNew game: " << kRows << " x " << kCols << " board with "
              << kMineCount << " mines. Good luck!\n";

    while (true)
    {
        PrintStatus(board);
        board.Print();

        char action = Input::ReadChoice(
            "Choose an action - (R)eveal, (F)lag/unflag, or (Q)uit to menu: ", "RFQ");
        if (action == 'Q')
        {
            std::cout << "Returning to the main menu.\n";
            return RoundResult::QuitToMenu;
        }

        int row = Input::ReadInt("Row (1-" + std::to_string(kRows) + "), or 0 to cancel: ", 0, kRows);
        if (row == 0)
        {
            continue;
        }
        int col = Input::ReadInt("Column (1-" + std::to_string(kCols) + "), or 0 to cancel: ", 0, kCols);
        if (col == 0)
        {
            continue;
        }

        // Players use numbers starting at 1, the board uses indexes starting at 0.
        if (action == 'F')
        {
            HandleFlag(board, row - 1, col - 1);
            continue;
        }

        switch (board.RevealCell(row - 1, col - 1))
        {
        case Board::RevealResult::AlreadyRevealed:
            std::cout << "That cell is already revealed. Try another one.\n";
            break;
        case Board::RevealResult::Flagged:
            std::cout << "That cell is flagged. Unflag it first if you want to reveal it.\n";
            break;
        case Board::RevealResult::HitMine:
            board.RevealAllMines();
            board.Print();
            std::cout << "BOOM! You hit a mine. Game over.\n";
            return RoundResult::Lost;
        case Board::RevealResult::Invalid:
            std::cout << "That position is off the board.\n";
            break;
        case Board::RevealResult::Safe:
            if (board.AllSafeCellsRevealed())
            {
                board.Print();
                std::cout << "You cleared every safe cell. You win!\n";
                return RoundResult::Won;
            }
            break;
        }
    }
}
