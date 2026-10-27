#include "../include/Game.h"
#include "../include/Board.h"
#include "../include/Input.h"

#include <iostream>
#include <string>

namespace
{
    constexpr int kMenuNewGame = 1;
    constexpr int kMenuQuit = 2;
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
            PlayRound();
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
    std::cout << kMenuQuit << ". Quit\n";
}

void Game::PlayRound()
{
    Board board(kRows, kCols);
    std::cout << "\nNew game started on a " << kRows << " x " << kCols << " board.\n";

    while (true)
    {
        board.Print();

        int row = Input::ReadInt("Enter a row (1-" + std::to_string(kRows) +
                                 "), or 0 to return to the menu: ", 0, kRows);
        if (row == 0)
        {
            std::cout << "Returning to the main menu.\n";
            return;
        }

        int col = Input::ReadInt("Enter a column (1-" + std::to_string(kCols) + "): ", 1, kCols);

        // Players use numbers starting at 1, the board uses indexes starting at 0.
        if (!board.RevealCell(row - 1, col - 1))
        {
            std::cout << "That cell is already revealed. Try another one.\n";
        }
    }
}
