#include "Team.h"
#include <algorithm>

Team::Team(const std::string& teamName) : m_teamName(teamName), m_score(0) {}

void Team::addPlayer(const Player& player) {
    m_players.push_back(player);
}

void Team::removePlayer(const std::string& playerName) {
    auto it = std::find_if(m_players.begin(), m_players.end(),
        [&playerName](const Player& player) { return player.getName() == playerName; });
    if (it != m_players.end()) {
        m_players.erase(it);
    }
}

int Team::getScore() const {
    return m_score;
}

void Team::updateScore(int points) {
    m_score += points;
}

bool Team::hasPlayer(const std::string& playerName) const {
    return std::any_of(m_players.begin(), m_players.end(),
        [&playerName](const Player& player) { return player.getName() == playerName; });
}

Player* Team::findPlayer(const std::string& playerName) {
    auto it = std::find_if(m_players.begin(), m_players.end(),
        [&playerName](Player& player) { return player.getName() == playerName; });
    return it != m_players.end() ? &(*it) : nullptr;
}
