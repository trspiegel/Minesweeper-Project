#include "../include/Input.h"

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

int Input::ReadInt(const std::string& prompt, int min, int max)
{
    while (true)
    {
        std::cout << prompt;

        std::string line;
        if (!std::getline(std::cin, line))
        {
            // The input stream was closed (for example, Ctrl+Z), so there is
            // nothing left to read. Exit cleanly instead of looping forever.
            std::cout << "\nInput closed. Exiting.\n";
            std::exit(0);
        }

        try
        {
            std::size_t charsUsed = 0;
            int value = std::stoi(line, &charsUsed);

            // Allow trailing spaces, but reject things like "5abc".
            while (charsUsed < line.size() &&
                   std::isspace(static_cast<unsigned char>(line[charsUsed])))
            {
                ++charsUsed;
            }

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
