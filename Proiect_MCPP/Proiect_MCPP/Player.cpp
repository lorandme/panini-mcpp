#include "Player.h"
#include <iostream>
#include <algorithm>

Player::Player(int id, int startX, int startY)
    : m_id(id), m_x(startX), m_y(startY),
    m_lastMoveTime(0.0f),
    m_currentMoveCooldown(m_baseMoveCooldown) {
}

Player::Player(const std::string& name, int startX, int startY)
    : m_playername(name), m_x(startX), m_y(startY),
    m_lastMoveTime(0.0f),
    m_currentMoveCooldown(m_baseMoveCooldown) {
}

void Player::setX(int x) {
    m_x = x;
}

void Player::setY(int y) {
    m_y = y;
}

void Player::setPlayerName(const std::string& playerName) {
    m_playername = playerName;
}

void Player::setLastDirection(Direction dir) {
    m_lastDirection = dir;
}

std::pair<int, int> Player::getPosition() const {
    return { m_x, m_y };
}

int Player::getScore() const {
    return m_score;
}

int Player::getLives() const {
    return m_lives;
}

int Player::getId() const {
    return m_id;
}

int Player::getX() const {
    return m_x;
}

int Player::getY() const {
    return m_y;
}

std::string Player::getName() const {
    return m_playername;
}

void Player::addScore(int points)
{
    m_score += points;
}

void Player::resetScore() {
    m_score = 0;
    m_kills = 0;
}

void Player::incrementKills() {
    m_kills++;
}

int Player::getKills() const {
    return m_kills;
}

Direction Player::getLastDirection() const {
    return m_lastDirection;
}

void Player::move(int deltaX, int deltaY, float deltaTime) {
    m_lastMoveTime += deltaTime;

    if (m_lastMoveTime >= m_currentMoveCooldown) {
        m_x += deltaX;
        m_y += deltaY;
        m_lastMoveTime = 0.0f;

        if (deltaX < 0) m_lastDirection = Direction::LEFT;
        else if (deltaX > 0) m_lastDirection = Direction::RIGHT;
        else if (deltaY < 0) m_lastDirection = Direction::UP;
        else if (deltaY > 0) m_lastDirection = Direction::DOWN;
    }
}

void Player::shoot() {
}

void Player::loseLife() {
    if (m_lives > 0) {
        --m_lives;
    }
}

void Player::addReward(int points) {
    m_score += points;
}

void Player::addHP(int hp) {
    m_lives = std::min(m_lives + hp, MAX_LIVES);
}

void Player::gainLife() {
    if (m_lives < MAX_LIVES) {
        ++m_lives;
    }
}

void Player::activateSpeedBoost() {
    m_speedBoosted = true;
    m_speedBoostTimer = SPEED_BOOST_DURATION;

    m_currentMoveCooldown = m_baseMoveCooldown * SPEED_BOOST_MULTIPLIER;
}

void Player::activateShield() {
    m_hasShield = true;
    m_shieldTimer = SHIELD_DURATION;
}

bool Player::hasShield() const {
    return m_hasShield;
}

bool Player::isSpeedBoosted() const {
    return m_speedBoosted;
}

void Player::updatePowerUps(float deltaTime) {
    if (m_hasShield) {
        m_shieldTimer -= deltaTime;
        if (m_shieldTimer <= 0) {
            m_hasShield = false;
            m_shieldTimer = 0;
        }
    }

    if (m_speedBoosted) {
        m_speedBoostTimer -= deltaTime;
        if (m_speedBoostTimer <= 0) {
            m_speedBoosted = false;
            m_speedBoostTimer = 0;

            m_currentMoveCooldown = m_baseMoveCooldown;
        }
    }
}


void Player::collectPowerUp(PowerUp::Type powerUpType) {
    switch (powerUpType) {
    case PowerUp::EXTRA_HP:
        gainLife();
        break;
    case PowerUp::SHIELD:
        activateShield();
        break;
    case PowerUp::SPEED_BOOST:
        activateSpeedBoost();
        break;
    }
}

bool Player::isEliminated() const {
    return m_lives <= 0;
}

bool Player::hasWon() const {
    return false;
}

bool Player::operator==(const Player& other) const {
    return m_id == other.m_id;
}

bool Player::operator!=(const Player& other) const {
    return !(*this == other);
}

void Player::debugLastDirection() const {
    std::cout << "Player Last Direction: ";
    switch (m_lastDirection) {
    case Direction::UP:
        std::cout << "UP";
        break;
    case Direction::DOWN:
        std::cout << "DOWN";
        break;
    case Direction::LEFT:
        std::cout << "LEFT";
        break;
    case Direction::RIGHT:
        std::cout << "RIGHT";
        break;
    }
    std::cout << std::endl;
}