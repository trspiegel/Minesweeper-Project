#include "../include/Input.h"

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace
{
    // Reads one line from the player. If the input stream is closed
    // (for example, Ctrl+Z), there is nothing left to read, so the program
    // exits cleanly instead of looping forever.
    std::string ReadLine()
    {
        std::string line;
        if (!std::getline(std::cin, line))
        {
            std::cout << "\nInput closed. Exiting.\n";
            std::exit(0);
        }
        return line;
    }

    // Removes spaces and tabs from both ends of the text.
    std::string Trim(const std::string& text)
    {
        const std::string whitespace = " \t\r\n";
        std::size_t start = text.find_first_not_of(whitespace);
        if (start == std::string::npos)
        {
            return "";
        }
        std::size_t end = text.find_last_not_of(whitespace);
        return text.substr(start, end - start + 1);
    }
}

int Input::ReadInt(const std::string& prompt, int min, int max)
{
    while (true)
    {
        std::cout << prompt;
        std::string line = Trim(ReadLine());

        try
        {
            std::size_t charsUsed = 0;
            int value = std::stoi(line, &charsUsed);

            // Reject things like "5abc" where only part of the text is a number.
            if (charsUsed == line.size() && value >= min && value <= max)
            {
                return value;
            }
        }
        catch (const std::exception&)
        {
            // std::stoi throws if the text isn't a number or is too large.
            // Fall through to the error message below.
        }

        std::cout << "Please enter a whole number from " << min << " to " << max << ".\n";
    }
}

char Input::ReadChoice(const std::string& prompt, const std::string& validChoices)
{
    while (true)
    {
        std::cout << prompt;
        std::string line = Trim(ReadLine());

        if (line.size() == 1)
        {
            char choice = static_cast<char>(std::toupper(static_cast<unsigned char>(line[0])));
            if (validChoices.find(choice) != std::string::npos)
            {
                return choice;
            }
        }

        // List the valid letters, for example "R, F, or Q" or "Y or N".
        std::size_t count = validChoices.size();
        std::cout << "Please enter ";
        for (std::size_t i = 0; i < count; ++i)
        {
            if (i > 0 && i + 1 == count)
            {
                std::cout << (count == 2 ? " or " : ", or ");
            }
            else if (i > 0)
            {
                std::cout << ", ";
            }
            std::cout << validChoices[i];
        }
        std::cout << ".\n";
    }
}
