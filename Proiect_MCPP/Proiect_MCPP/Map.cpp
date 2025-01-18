#include "Map.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <SFML/Graphics.hpp>

Map::Map(int width, int height) : m_width(width), m_height(height) {
    m_grid.resize(height, std::vector<Tile>(width));
    generateRandom();
}

int Map::getWidth() const {
    return m_width;
}

int Map::getHeight() const {
    return m_height;
}

Tile& Map::getTile(int x, int y) {
    if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
        throw std::out_of_range("Tile coordinates out of bounds");
    }
    return m_grid[y][x];
}

const Tile& Map::getTile(int x, int y) const {
    if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
        throw std::out_of_range("Tile coordinates out of bounds");
    }
    return m_grid[y][x];
}

void Map::generateRandom() {
    srand(static_cast<unsigned int>(time(0)));
    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            int randomValue = rand() % 10;
            if (randomValue < 2) {
                m_grid[y][x].setType(TileType::WALL);
            }
            else if (randomValue < 4) {
                m_grid[y][x].setType(TileType::DESTRUCTIBLE_WALL);
            }
            else {
                m_grid[y][x].setType(TileType::EMPTY);
            }
        }
    }
    int centerX = m_width / 2;
    int centerY = m_height / 2;

    createPath(0, 0, centerX, centerY);
    createPath(0, m_height - 1, centerX, centerY);
    createPath(m_width - 1, 0, centerX, centerY);
    createPath(m_width - 1, m_height - 1, centerX, centerY);
}

void Map::createPath(int startX, int startY, int targetX, int targetY) {
    for (int x = startX; x != targetX; x += (targetX > startX ? 1 : -1)) {
        m_grid[startY][x].setType(TileType::EMPTY);
    }

    for (int y = startY; y != targetY; y += (targetY > startY ? 1 : -1)) {
        m_grid[y][targetX].setType(TileType::EMPTY);
    }
}

void Map::addPlayer(const Player& player) {
    if (player.getX() >= 0 && player.getX() < m_width &&
        player.getY() >= 0 && player.getY() < m_height &&
        getTile(player.getX(), player.getY()).isWalkable()) {
        m_players.push_back(player);
    }
    else {
        std::cerr << "Cannot place player on a non-walkable tile or out of bounds." << std::endl;
    }
}

bool Map::movePlayer(int playerId, int deltaX, int deltaY, float deltaTime) {
    auto playerIt = std::find_if(m_players.begin(), m_players.end(),
        [playerId](const Player& p) { return p.getId() == playerId; });

    if (playerIt == m_players.end()) {
        std::cerr << "Player with ID " << playerId << " not found." << std::endl;
        return false;
    }

    if (playerIt->isEliminated()) {
        std::cerr << "Player " << playerId << " is eliminated." << std::endl;
        return false;
    }

    float moveCooldown = playerIt->getMoveCooldown();

    playerIt->incrementLastMoveTime(deltaTime);

    if (playerIt->getLastMoveTime() < moveCooldown) {
        return false;
    }

    int currentX = playerIt->getX();
    int currentY = playerIt->getY();
    int newX = currentX + deltaX;
    int newY = currentY + deltaY;

    if (newX < 0 || newX >= m_width || newY < 0 || newY >= m_height) {
        std::cerr << "Move out of bounds: (" << newX << ", " << newY << ")" << std::endl;
        return false;
    }

    if (!getTile(newX, newY).isWalkable()) {
        std::cerr << "Tile at (" << newX << ", " << newY << ") is not walkable" << std::endl;
        return false;
    }

    bool playerOnTile = std::any_of(m_players.begin(), m_players.end(),
        [newX, newY](const Player& p) {
            return p.getX() == newX && p.getY() == newY;
        });

    if (playerOnTile) {
        std::cerr << "Another player is on tile (" << newX << ", " << newY << ")" << std::endl;
        return false;
    }

    bool bombOnTile = std::any_of(m_bombs.begin(), m_bombs.end(),
        [newX, newY](const Bomb& bomb) {
            return bomb.getX() == newX && bomb.getY() == newY;
        });

    if (bombOnTile) {
        std::cerr << "Cannot move: A bomb is on tile (" << newX << ", " << newY << ")" << std::endl;
        return false;
    }

    playerIt->setX(newX);
    playerIt->setY(newY);

    playerIt->resetLastMoveTime();

    if (deltaX < 0) playerIt->setLastDirection(Direction::LEFT);
    else if (deltaX > 0) playerIt->setLastDirection(Direction::RIGHT);
    else if (deltaY < 0) playerIt->setLastDirection(Direction::UP);
    else if (deltaY > 0) playerIt->setLastDirection(Direction::DOWN);

    return true;
}

void Map::printPlayerPositions() const {
    for (const auto& player : m_players) {
        std::cout << "Player ID: " << player.getId()
            << " Position: (" << player.getX() << ", " << player.getY() << ")" << std::endl;
    }
}

bool Map::canMoveToTile(int x, int y) {
    if (!getTile(x, y).isWalkable()) {
        return false;
    }

    for (const auto& player : m_players) {
        if (player.getX() == x && player.getY() == y) {
            return false;
        }
    }

    return true;
}


void Map::shootBullet(Player& player) {
    auto playerIt = std::find_if(m_players.begin(), m_players.end(),
        [&player](const Player& p) { return p.getId() == player.getId(); });

    if (playerIt == m_players.end()) {
        std::cerr << "Cannot shoot - player not found" << std::endl;
        return;
    }

    auto currentPlayerPos = player.getPosition();
    int playerX = currentPlayerPos.first;
    int playerY = currentPlayerPos.second;

    Direction bulletDirection = player.getLastDirection();

    size_t playerIndex = std::distance(m_players.begin(), playerIt);

    m_bullets.emplace_back(
        static_cast<double>(playerX),
        static_cast<double>(playerY),
        bulletDirection,
        playerIndex
    );
}

void Map::updateBullets(float deltaTime) {
    auto bulletIt = m_bullets.begin();

    while (bulletIt != m_bullets.end()) {
        if (!bulletIt->isBulletActive() ||
            isOutOfBounds(*bulletIt) ||
            checkBulletCollisions(*bulletIt)) {

            bulletIt = m_bullets.erase(bulletIt);
        }
        else {
            bulletIt->move(deltaTime);
            ++bulletIt;
        }
    }
}

bool Map::isOutOfBounds(const Bullet& bullet) const {
    auto pos = bullet.getPosition();
    return pos.first < 0 || pos.first >= m_width ||
        pos.second < 0 || pos.second >= m_height;
}

bool Map::checkBulletCollisions(Bullet& bullet) {
    for (size_t i = 0; i < m_players.size(); ++i) {
        auto& player = m_players[i];
        if (bullet.checkCollision(player.getX(), player.getY()) && i != bullet.getOwner()) {
            if (!player.hasShield()) {
                player.loseLife();
                std::cout << "Player " << player.getId() << " hit! Remaining lives: " << player.getLives() << std::endl;

                if (player.isEliminated()) {
                    std::cout << "Player " << player.getId() << " has been eliminated!" << std::endl;
                }
            }
            bullet.deactivate();
            return true;
        }
    }

    auto pos = bullet.getPosition();
    int tileX = static_cast<int>(pos.first);
    int tileY = static_cast<int>(pos.second);
    Tile& tile = getTile(tileX, tileY);

    if (!tile.isWalkable()) {
        if (tile.isDestructible()) {
            spawnBombOnDestruction(tileX, tileY);
            tile.destroy();
        }
        bullet.deactivate();
        return true;
    }

    for (auto& otherBullet : m_bullets) {
        if (&otherBullet != &bullet &&
            bullet.checkCollision(
                static_cast<int>(otherBullet.getPosition().first),
                static_cast<int>(otherBullet.getPosition().second)
            )) {
            bullet.deactivate();
            otherBullet.deactivate();
            return true;
        }
    }

    return false;
}

void Map::removeEliminatedPlayers() {
    m_players.erase(
        std::remove_if(m_players.begin(), m_players.end(),
            [](const Player& player) {
                return player.isEliminated();
            }),
        m_players.end()
    );
}

void Map::spawnBombOnDestruction(int x, int y) {
    if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
        std::cout << "Bomb spawn failed: Out of bounds" << std::endl;
        return;
    }

    Tile& tile = getTile(x, y);
    if (!tile.isDestructible()) {
        std::cout << "Bomb spawn failed: Tile not destructible" << std::endl;
        return;
    }
    std::uniform_real_distribution<> distribution(0.0, 1.0);
    double randomValue = distribution(m_randomGenerator);

    std::cout << "Random value: " << randomValue << std::endl;

    if (randomValue <= 0.2) {
        std::cout << "Bomb spawned at (" << x << ", " << y << ")" << std::endl;

        m_bombs.emplace_back(x, y, -1);
    }
    else {
        std::cout << "Bomb not spawned. Random value too high." << std::endl;
    }
}

std::vector<Bomb>& Map::getBombs() {
    return m_bombs;
}

const std::vector<Bomb>& Map::getBombs() const {
    return m_bombs;
}

void Map::updateBombs(float deltaTime) {
    for (auto it = m_bombs.begin(); it != m_bombs.end();) {
        it->update(deltaTime);

        if (it->isExploded()) {
            if (!it->hasDamageDone()) {
                for (auto& player : m_players) {
                    if (isPlayerInExplosionRadius(player, it->getX(), it->getY())) {
                        player.loseLife();
                        std::cout << "Player " << player.getId() << " damaged by bomb!" << std::endl;
                    }
                }
                it->setDamageDone(true);
            }

            if (it->getTimer() > 1.0f) {
                it = m_bombs.erase(it);
                continue;
            }
            else {
                ++it;
            }
        }
        else {
            ++it;
        }
    }
}

bool Map::isPlayerInExplosionRadius(Player& player, int bombX, int bombY) {
    int playerX = player.getX();
    int playerY = player.getY();

    return (std::abs(playerX - bombX) <= 1 && playerY == bombY) ||
        (std::abs(playerY - bombY) <= 1 && playerX == bombX);
}

void Map::updatePowerUps(float deltaTime) {
    m_powerUpTimer += deltaTime;

    if (m_powerUpTimer >= POWERUP_SPAWN_INTERVAL) {
        m_powerUpTimer = 0.0f;

        std::vector<std::pair<int, int>> emptyTiles;
        for (int y = 0; y < m_height; ++y) {
            for (int x = 0; x < m_width; ++x) {
                if (m_grid[y][x].getType() == TileType::EMPTY &&
                    std::none_of(m_players.begin(), m_players.end(),
                        [x, y](const Player& p) { return p.getX() == x && p.getY() == y; }) &&
                    std::none_of(m_bombs.begin(), m_bombs.end(),
                        [x, y](const Bomb& b) { return b.getX() == x && b.getY() == y; })) {
                    emptyTiles.push_back({ x, y });
                }
            }
        }

        if (!emptyTiles.empty()) {
            std::uniform_int_distribution<> tileDist(0, emptyTiles.size() - 1);
            std::uniform_int_distribution<> typeDist(0, 2);

            auto selectedTile = emptyTiles[tileDist(m_randomGenerator)];

            PowerUp::Type randomType = static_cast<PowerUp::Type>(typeDist(m_randomGenerator));
            m_powerUps.emplace_back(selectedTile.first, selectedTile.second, randomType);
        }
    }
}

void Map::collectPowerUps(Player& player) {
    auto it = m_powerUps.begin();
    while (it != m_powerUps.end()) {
        if (it->getX() == player.getX() && it->getY() == player.getY()) {
            player.collectPowerUp(it->getType());

            it = m_powerUps.erase(it);
        }
        else {
            ++it;
        }
    }
}

