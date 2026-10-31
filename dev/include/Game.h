#pragma once

// Controls the flow of the program: the main menu and each round of play.
class Game
{
public:
    // Runs the main menu loop until the player chooses Quit.
    void Run();

private:
    // Board size for now. Difficulty levels will change this in a later milestone.
    static constexpr int kRows = 9;
    static constexpr int kCols = 9;

    void ShowMainMenu() const;
    void PlayRound();
};
