#pragma once

#include <string>

// Helper functions for reading input from the player.
namespace Input
{
    // Shows the prompt and keeps asking until the player types a whole
    // number from min to max. Letters, extra characters, and numbers
    // outside the range are rejected with a message.
    int ReadInt(const std::string& prompt, int min, int max);
}
