#pragma once

#include <vector>
#include <string>
#include "Player.h"

class Team {
private:
    std::string m_teamName;
    std::vector<Player> m_players;
    int m_score;

public:
    Team(const std::string& name);

    void addPlayer(const Player& player);
    void removePlayer(const std::string& playerName);

    int getScore() const;
    void updateScore(int points);

    std::string getName() const { return m_teamName; }
    std::vector<Player> getPlayers() const { return m_players; }

    bool hasPlayer(const std::string& playerName) const;
    Player* findPlayer(const std::string& playerName);
};
