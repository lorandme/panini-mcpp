#pragma once

#include "Player.h"
#include "Map.h"
#include <vector>

class GameManager {
private:
    Map m_gameMap;                 
    std::vector<Player> m_players;
    bool m_isRunning;              

public:
    GameManager();
    void initializeGame();
    void startGame();
    void gameLoop();
    void endGame();

    std::vector<Player>& getPlayers();
    void detectCollisions();
    void updateGameState();
    void handlePlayerMovement(const std::string& playerName, const char direction);
    void handlePlayerShooting(const std::string& playerName, const Direction& dir);
};
