#include "Team.h"
#include <algorithm>

Team::Team(const std::string& name) : teamName(name), score(0) {}

void Team::addPlayer(const Player& player) {
    players.push_back(player);
}

void Team::removePlayer(const std::string& playerName) {
    for (auto it = players.begin(); it != players.end(); ++it) {
        if (it->getName() == playerName) {
            players.erase(it);
            break;
        }
    }
}

int Team::getScore() const {
    return score;
}

void Team::updateScore(int points) {
    score += points;
}

bool Team::hasPlayer(const std::string& playerName) const {
    for (const auto& player : players) {
        if (player.getName() == playerName) {
            return true;
        }
    }
    return false; 
}

Player* Team::findPlayer(const std::string& playerName) {
    for (auto& player : players) {
        if (player.getName() == playerName) {
            return &player;
        }
    }
    return nullptr;
}