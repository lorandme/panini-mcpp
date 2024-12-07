#include "Player.h"
#include <iostream>
#include <stdexcept>

Player::Player(const std::string& username, int startX, int startY)
    : m_playername(username), m_x(startX), m_y(startY), m_team(nullptr) {}

bool Player::checkCollisionWithEnemies() {
    return true; // TODO: dacă se află un alt jucător pe această poziție să nu poată să se mute
}

void Player::moveUp() { m_y--; }
void Player::moveDown() { m_y++; }
void Player::moveLeft() { m_x--; }
void Player::moveRight() { m_x++; }

void Player::movePlayer(char direction, int maxX, int maxY, const Map& map) {
    int newX = m_x;
    int newY = m_y;

    switch (direction) {
    case 'w': newY--; break; // Move up
    case 's': newY++; break; // Move down
    case 'a': newX--; break; // Move left
    case 'd': newX++; break; // Move right
    default: return; // Invalid direction
    }

    // Verifică dacă jucătorul poate să se mute pe noua poziție
    if (canMoveTo(map, newX, newY)) {
        m_x = newX;
        m_y = newY;
    }
}

void Player::handleInput()
{
}

bool Player::canMoveTo(const Map& map, int newX, int newY) const {
    // Verifică dacă coordonatele sunt în afara granițelor hărții
    if (newX < 0 || newY < 0 || newX >= map.getWidth() || newY >= map.getHeight()) {
        return false;
    }

    // Obține tipul de celulă la poziția respectivă
    const Tile& targetTile = map.getTile(newX, newY);

    // Jucătorul nu se poate muta dacă celula este un perete sau un perete destructibil
    if (targetTile.getType() == TileType::WALL || targetTile.getType() == TileType::DESTRUCTIBLE_WALL) {
        return false;
    }

    return true;
}

std::string Player::getName() const {
    return m_playername; // Return the player's name
}

Weapon& Player::getWeapon() {
    return m_weapon;
}

Team* Player::getTeamName() const
{
    return nullptr;
}

void Player::setTeam(Team* newTeam)
{
}

void Player::shoot() {
    // Implement shooting logic here
}

void Player::loseLife() {
    if (m_lives > 0) {
        m_lives--;
    }
}

bool Player::isEliminated() const {
    return m_lives <= 0;
}

bool Player::hasWon() const {
    // Implement winning condition logic here
    return false;
}

std::pair<int, int> Player::getPosition() const {
    return std::make_pair(m_x, m_y); // Return the player's current position
}

int Player::getScore() const {
    return m_score; // Return the player's score
}

int Player::getLives() const {
    return m_lives; // Return the number of lives left
}

void Player::updateScore(int points) {
    m_score += points; // Update the player's score
}

void Player::setPlayerName(const std::string& playerName) {
    m_playername = playerName; // Set the player's name
}

void Player::addReward(int points) {
    m_score += points; // Adaugă punctele la scorul jucătorului
    std::cout << m_playername << " a primit " << points << " puncte!\n";
}
