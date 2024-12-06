#include "ScoreBoard.h"
#include <iostream>
#include <unordered_map>

ScoreBoard::ScoreBoard() : isTeamMode(false) {}

void ScoreBoard::setTeamMode(bool teamMode) {
    isTeamMode = teamMode;
}

void ScoreBoard::addPlayer(const Player& player) {
    players.push_back(player);
}

void ScoreBoard::updateScore(const std::string& playerName, int points) {
    for (auto& player : players) {
        if (player.getName() == playerName) {
            player.updateScore(points);
            break;
        }
    }
}

void ScoreBoard::displayScores() const {
    std::cout << "Scoruri curente:\n";
    for (const auto& player : players) {
        std::cout << player.getName() << " - " << player.getScore() << " puncte\n";
    }
}

Player* ScoreBoard::getPlayer(const std::string& playerName) {
    for (auto& player : players) {
        if (player.getName() == playerName) {
            return &player;
        }
    }
    return nullptr;
}

bool ScoreBoard::hasPlayer(const std::string& playerName) const {
    for (const auto& player : players) {
        if (player.getName() == playerName) {
            return true;
        }
    }
    return false;
}

void ScoreBoard::displayTeamScores() const {
    if (!isTeamMode) {
        std::cout << "Nu se joac? în echipe.\n";
        return;
    }

    std::unordered_map<std::string, int> teamScores;

    for (const auto& player : players) {
        teamScores[player.getName()] += player.getScore();
    }

    std::cout << "Scoruri echipe:\n";
    for (const auto& team : teamScores) {
        std::cout << team.first << " - " << team.second << " puncte\n";
    }
}
