//#pragma once
//
//#include "Player.h"
//#include "Map.h"
//#include <vector>
//#include "PowerUp.h"
//
//
//class GameManager {
//private:
//    Map m_gameMap;                 
//    std::vector<Player> m_players;
//    std::vector<PowerUp> m_powerUps;
//    bool m_isRunning;              
//
//public:
//    GameManager();
//    void initializeGame();
//    void startGame();
//    void gameLoop();
//    void endGame();
//
//    std::vector<Player>& getPlayers();
//    void detectCollisions();
//    void updateGameState();
//    void handlePlayerMovement(const std::string& playerName, const char direction);
//    void handlePlayerShooting(const std::string& playerName, const Direction& dir);
//    void generatePowerUps(int count);
//    void checkPlayerPowerUpCollision();
//    void renderMap() const;
//
//};
