#include "PlayerLogger.h"

PlayerLogger::PlayerLogger(const std::string& fileName, Level minimumLevel)
    : m_ofs(fileName), m_minimumLevel(minimumLevel) {
}

void PlayerLogger::LogPlayerMove(const std::string& playerName, int x, int y) {
    Log("Player " + playerName + " moved to position (" + std::to_string(x) + ", " + std::to_string(y) + ")", Level::Info);
}

void PlayerLogger::LogPlayerScore(const std::string& playerName, int score) {
    Log("Player " + playerName + " scored " + std::to_string(score), Level::Info);
}

void PlayerLogger::LogPlayerDeath(const std::string& playerName) {
    Log("Player " + playerName + " died.", Level::Error);
}

void PlayerLogger::LogPowerUpCollect(const std::string& playerName, int powerUpType) {
    Log("Player " + playerName + " collected power-up type " + std::to_string(powerUpType), Level::Info);
}

void PlayerLogger::Log(const std::string& message, Level level) {
    if (level >= m_minimumLevel) {
        m_ofs << message << std::endl;
    }
}
