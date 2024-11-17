#include "Team.h"
#include <algorithm>

Team::Team(const std::string& name): teamName(name),score(0){}

void Team::addPlayer(const Player& player) {
	players.push_back(player);
}

void Team::removePlayer(const std::string& playerName) {
    players.erase(std::remove_if(players.begin(), players.end(),
        [&](const Player& p) { return p.getName() == playerName; }), players.end());
}

int Team::getScore() const {
    return score;
}

void Team::updateScore(int points) {
    score += points;
}

bool Team::hasPlayer(const std::string& playerName) const {
    return std::any_of(players.begin(), players.end(),
        [&](const Player& p) { return p.getName() == playerName; });
}

Player* Team::findPlayer(const std::string& playerName) {
    for (auto& player : players) {
        if (player.getName() == playerName) {
            return &player;
        }
        return nullptr;
    }
}