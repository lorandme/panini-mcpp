#pragma once
#include "Map.h"
#include "PlayerDisplay.h"
#include "MapDisplay.h"
#include "BulletDisplay.h"
#include "BombDisplay.h"
#include "PowerUpDisplay.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

class GameManager {
public:
    GameManager(int mapWidth, int mapHeight, float tileSize);
    void run();
    void checkGameOver();
    void endGame();
    void displayGameOverScreen(const std::string& message);

private:
    const int mapWidth;
    const int mapHeight;
    const float tileSize;

    Map gameMap;
    TileDisplay tileDisplay;
    MapDisplay mapDisplay;
    std::map<int, PlayerDisplay> playerDisplays;
    std::vector<BulletDisplay> bulletDisplays;
    std::vector<BombDisplay> bombDisplays;
    std::vector<PowerUpDisplay> powerUpDisplays;


    sf::RenderWindow window;

    sf::Clock gameClock;
    sf::Clock movementClock1, movementClock2;
    sf::Clock shootClock1, shootClock2;

    const float movementCooldown = 0.2f;
    const float shootCooldown = 0.5f;

    void handleEvents();
    void updateGame(float deltaTime);
    void handlePlayerMovement(float deltaTime);
    void handlePlayerShooting();
    void updateDisplays(float deltaTime);
    void render();
};
