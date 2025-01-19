#pragma once

#include <string>
#include <fstream>

#ifdef _WIN32
#define PLAYERLOG_DLL_EXPORT __declspec(dllexport)
#else
#define PLAYERLOG_DLL_EXPORT
#endif

class PLAYERLOG_DLL_EXPORT PlayerLogger {
public:
    enum class Level : char {
        Info,
        Warning,
        Error
    };

    PlayerLogger(const std::string& fileName, Level minimumLevel = Level::Info);
    void LogPlayerMove(const std::string& playerName, int x, int y);
    void LogPlayerScore(const std::string& playerName, int score);
    void LogPlayerDeath(const std::string& playerName);
    void LogPowerUpCollect(const std::string& playerName, int powerUpType);

private:
    std::ofstream m_ofs;
    Level m_minimumLevel;

    void Log(const std::string& message, Level level);
};
