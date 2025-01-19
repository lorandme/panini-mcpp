#pragma once

#include <vector>
#include <random>
#include "Tile.h"
#include "Player.h"
#include "Bullet.h"
#include "Bomb.h"
#include "PowerUp.h"

class Map {
private:
    int m_width;
    int m_height;
    std::vector<std::vector<Tile>> m_grid;
    std::vector<Player> m_players;
    std::vector<Bullet> m_bullets;
    std::vector<Bomb> m_bombs;
    std::random_device m_randomDevice;
    std::mt19937 m_randomGenerator{ m_randomDevice() };

    float m_powerUpTimer = 0.0f;
    const float POWERUP_SPAWN_INTERVAL = 10.0f;
    std::vector<PowerUp> m_powerUps;

public:
    Map(int width, int height);

    int getWidth() const;
    int getHeight() const;
    Tile& getTile(int x, int y);
    const Tile& getTile(int x, int y) const;
    std::vector<Player>& getPlayers() { return m_players; }
    const std::vector<Player>& getPlayers() const { return m_players; }
    std::vector<Bullet>& getBullets() { return m_bullets; }
    std::vector<Bomb>& getBombs();
    const std::vector<Bomb>& getBombs() const;

    std::vector<PowerUp>& getPowerUps() { return m_powerUps; }
    const std::vector<PowerUp>& getPowerUps() const { return m_powerUps; }

    void generateRandom();
    void createPath(int startX, int startY, int targetX, int targetY);

    void addPlayer(const Player& player);
    bool movePlayer(int playerId, int deltaX, int deltaY, float deltaTime);
    void printPlayerPositions() const;
    bool canMoveToTile(int x, int y);
    void removeEliminatedPlayers();

    void shootBullet(Player& player);
    void updateBullets(float deltaTime);

    void spawnBombOnDestruction(int x, int y);
    void updateBombs(float deltaTime);

    void updatePowerUps(float deltaTime);
    void collectPowerUps(Player& player);

private:
    bool isOutOfBounds(const Bullet& bullet) const;
    bool checkBulletCollisions(Bullet& bullet);
    bool isPlayerInExplosionRadius(Player& player, int bombX, int bombY);
};