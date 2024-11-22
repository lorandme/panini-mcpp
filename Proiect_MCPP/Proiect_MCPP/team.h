#pragma once

#include <vector>
#include <string>
#include "Player.h"

class Team {
private:
    std::string teamName;
    std::vector<Player> players;
    int score;

public:
    Team(const std::string& name);

    void addPlayer(const Player& player);
    void removePlayer(const std::string& playerName);

    int getScore() const;
    void updateScore(int points);

    std::string getName() const { return teamName; }
    std::vector<Player> getPlayers() const { return players; }

    bool hasPlayer(const std::string& playerName) const;
    Player* findPlayer(const std::string& playerName);
};