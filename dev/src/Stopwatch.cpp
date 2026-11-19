#include "../include/Stopwatch.h"

Stopwatch::Stopwatch()
    : m_running(false),
      m_startTime()
{
}

void Stopwatch::Start()
{
    if (m_running)
    {
        return;
    }
    m_running = true;
    m_startTime = std::chrono::steady_clock::now();
}

void Stopwatch::Reset()
{
    m_running = false;
    m_startTime = std::chrono::steady_clock::time_point();
}

bool Stopwatch::IsRunning() const
{
    return m_running;
}

int Stopwatch::GetElapsedSeconds() const
{
    if (!m_running)
    {
        return 0;
    }

    // steady_clock is used because it never jumps backward or forward
    // (for example, when the computer's clock changes for daylight saving time).
    std::chrono::steady_clock::duration elapsed = std::chrono::steady_clock::now() - m_startTime;
    return static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(elapsed).count());
}
