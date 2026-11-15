#include "../include/ScoreManager.h"

#include <fstream>
#include <sstream>

ScoreManager::ScoreManager(const std::string& fileName)
    : m_fileName(fileName)
{
    Load();
}

ScoreManager::RecordResult ScoreManager::RecordWin(const std::string& difficulty, int seconds)
{
    if (seconds < 0)
    {
        seconds = 0;
    }

    int bestSoFar = 0;
    if (GetBestTime(difficulty, bestSoFar) && seconds >= bestSoFar)
    {
        return RecordResult::NotABestTime;
    }

    m_bestTimes[difficulty] = seconds;
    if (!Save())
    {
        return RecordResult::NewBestTimeNotSaved;
    }
    return RecordResult::NewBestTime;
}

bool ScoreManager::GetBestTime(const std::string& difficulty, int& seconds) const
{
    std::map<std::string, int>::const_iterator found = m_bestTimes.find(difficulty);
    if (found == m_bestTimes.end())
    {
        return false;
    }
    seconds = found->second;
    return true;
}

std::string ScoreManager::FormatTime(int seconds)
{
    int minutes = seconds / 60;
    int leftover = seconds % 60;

    std::ostringstream text;
    text << minutes << ":" << (leftover < 10 ? "0" : "") << leftover;
    return text.str();
}

void ScoreManager::Load()
{
    std::ifstream file(m_fileName);
    if (!file)
    {
        // No file yet means no games have been won. That's not an error.
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream lineStream(line);
        std::string difficulty;
        int seconds = 0;
        std::string extra;

        // Each line should be exactly a name and a whole number, like "Easy 42".
        if (!(lineStream >> difficulty >> seconds) || (lineStream >> extra) || seconds < 0)
        {
            continue;
        }

        // If a difficulty somehow appears twice, keep the faster time.
        int existing = 0;
        if (!GetBestTime(difficulty, existing) || seconds < existing)
        {
            m_bestTimes[difficulty] = seconds;
        }
    }
}

bool ScoreManager::Save() const
{
    std::ofstream file(m_fileName);
    if (!file)
    {
        return false;
    }

    for (const std::pair<const std::string, int>& entry : m_bestTimes)
    {
        file << entry.first << " " << entry.second << "\n";
    }
    return static_cast<bool>(file);
}
