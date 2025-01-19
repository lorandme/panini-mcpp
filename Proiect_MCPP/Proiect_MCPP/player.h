#pragma once

#include <string>
#include <utility>
#include "Direction.h"
#include "PowerUp.h"

class Player {
private:
    std::string m_playername;
    int m_id;
    int m_x;
    int m_y;

    Direction m_lastDirection = Direction::DOWN;

    int m_lives = 3;
    static const int MAX_LIVES = 5;
    int m_score = 0;
    int m_kills = 0;


    float m_lastMoveTime = 0.0f;

    static constexpr float SHIELD_DURATION = 2.0f;
    static constexpr float SPEED_BOOST_DURATION = 5.0f;
    static constexpr float BASE_MOVE_COOLDOWN = 0.125f;
    static constexpr float SPEED_BOOST_MULTIPLIER = 0.5f;

    float m_baseMoveCooldown = BASE_MOVE_COOLDOWN;
    float m_currentMoveCooldown = BASE_MOVE_COOLDOWN;
    float m_shieldTimer = 0.0f;
    float m_speedBoostTimer = 0.0f;
    bool m_hasShield = false;
    bool m_speedBoosted = false;

public:
    Player(int id, int startX, int startY);
    Player(const std::string& name, int startX, int startY);

    void move(int deltaX, int deltaY, float deltaTime);
    void setLastDirection(Direction dir);
    Direction getLastDirection() const;

    float getMoveCooldown() const { return m_currentMoveCooldown; }
    float getLastMoveTime() const { return m_lastMoveTime; }
    void incrementLastMoveTime(float deltaTime) { m_lastMoveTime += deltaTime; }
    void resetLastMoveTime() { m_lastMoveTime = 0.0f; }

    void setX(int x);
    void setY(int y);
    void setPlayerName(const std::string& playerName);

    std::pair<int, int> getPosition() const;
    int getScore() const;
    int getLives() const;
    int getId() const;
    int getX() const;
    int getY() const;
    std::string getName() const;
    void addScore(int points);
    void resetScore();

    void incrementKills();
    int getKills() const;

    void shoot();
    void loseLife();
    void addReward(int points);
    void addHP(int hp);

    void gainLife();
    void activateShield();
    void activateSpeedBoost();
    bool hasShield() const;
    bool isSpeedBoosted() const;
    void updatePowerUps(float deltaTime);
    void collectPowerUp(PowerUp::Type powerUpType);

    bool isEliminated() const;
    bool hasWon() const;

    bool operator==(const Player& other) const;
    bool operator!=(const Player& other) const;

    void debugLastDirection() const;
};