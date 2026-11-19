#pragma once

#include <map>
#include <string>

// Keeps the fastest winning time (in seconds) for each difficulty level and
// saves the times to a text file, so they are still there the next time the
// game is opened.
class ScoreManager
{
public:
    // What happened when a win was recorded.
    enum class RecordResult
    {
        NotABestTime,        // Slower than (or tied with) the saved best time
        NewBestTime,         // A new best time, saved to the file
        NewBestTimeNotSaved  // A new best time, but the file couldn't be written
    };

    // Loads any best times already saved in the file. If the file doesn't
    // exist yet, the game simply starts with no best times.
    explicit ScoreManager(const std::string& fileName);

    // Records a winning time for a difficulty and saves it if it's a new best.
    RecordResult RecordWin(const std::string& difficulty, int seconds);

    // Returns true and sets seconds if the difficulty has a saved best time.
    bool GetBestTime(const std::string& difficulty, int& seconds) const;

    // True if at least one difficulty has a saved best time.
    bool HasAnyTimes() const;

    // Deletes every best time and saves the empty list to the file.
    // Returns false if the file couldn't be written.
    bool ClearAll();

    // Formats a number of seconds as minutes:seconds, for example 75 -> "1:15".
    static std::string FormatTime(int seconds);

private:
    // Reads "Name seconds" lines from the file. Lines that don't match that
    // format are skipped, so a damaged file can't crash the game.
    void Load();

    // Writes every best time to the file. Returns false if it can't be written.
    bool Save() const;

    std::string m_fileName;
    std::map<std::string, int> m_bestTimes;  // difficulty name -> best time in seconds
};
