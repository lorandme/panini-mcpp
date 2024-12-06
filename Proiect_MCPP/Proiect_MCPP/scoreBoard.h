#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "Player.h"  

class ScoreBoard {
private:
    std::vector<Player> players;
    bool isTeamMode;

public:
    ScoreBoard();

    void setTeamMode(bool teamMode);
    void addPlayer(const Player& player);
    void updateScore(const std::string& playerName, int points);
    void displayScores() const;
    Player* getPlayer(const std::string& playerName);
    bool hasPlayer(const std::string& playerName) const;
    void displayTeamScores() const;
};
