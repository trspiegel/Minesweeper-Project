#pragma once

#include <chrono>

// Measures how long a round has been played, in whole seconds.
// The clock doesn't run until Start() is called, so Game can start it on the
// player's first reveal instead of when the board first appears.
class Stopwatch
{
public:
    Stopwatch();

    // Starts timing from zero. Does nothing if the stopwatch is already running.
    void Start();

    // Stops the stopwatch and clears the time, ready for a new round.
    void Reset();

    // True once Start() has been called (until the next Reset()).
    bool IsRunning() const;

    // Seconds since Start() was called, or 0 if it hasn't started yet.
    int GetElapsedSeconds() const;

private:
    bool m_running;
    std::chrono::steady_clock::time_point m_startTime;
};
