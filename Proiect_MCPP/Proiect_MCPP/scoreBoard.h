#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "Player.h"  

class ScoreBoard {
private:
    std::vector<Player> players;  // Pentru echipe
    bool isTeamMode;  // Daca este mod de joc cu echipe

public:
    ScoreBoard() : isTeamMode(false) {}

    // Seteaza modul de joc (daca se joaca pe echipe sau nu)
    void setTeamMode(bool teamMode) {
        isTeamMode = teamMode;
    }

    // Adauga un jucător pe tabloul de scoruri
    void addPlayer(const Player& player) {
        players.push_back(player);
    }

    // Actualizeaza scorul unui jucator
    void updateScore(const std::string& playerName, int points) {
        for (auto& player : players) {
            if (player.getName() == playerName) {
                player.updateScore(points);
                break;
            }
        }
    }

    // Afiseaza scorurile curente
    void displayScores() const {
        std::cout << "Scoruri curente:\n";
        for (const auto& player : players) {
            std::cout << player.getName() << " - " << player.getScore() << " puncte\n";
        }
    }

    // Gaseste jucatorul in scoreboard
    Player* getPlayer(const std::string& playerName) {
        for (auto& player : players) {
            if (player.getName() == playerName) {
                return &player;
            }
        }
        return nullptr;
    }

    // Verifica daca jucatorul exista pe tabloul de scoruri
    bool hasPlayer(const std::string& playerName) const {
        for (const auto& player : players) {
            if (player.getName() == playerName) {
                return true;
            }
        }
        return false;
    }

    // Afiseaza scorurile in functie de echipe (daca este activat modul echipe)
    void displayTeamScores() const {
        if (!isTeamMode) {
            std::cout << "Nu se joacă în echipe.\n";
            return;
        }

        std::unordered_map<std::string, int> teamScores;

        // Adaugam scorurile echipelor
        for (const auto& player : players) {
            teamScores[player.getName()] += player.getScore();
        }

        std::cout << "Scoruri echipe:\n";
        for (const auto& team : teamScores) {
            std::cout << team.first << " - " << team.second << " puncte\n";
        }
    }

};
