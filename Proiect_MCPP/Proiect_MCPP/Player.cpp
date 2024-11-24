#include "weapon.h"
#include "map.h"
#include "account.h"
#include "player.h"
#include <iostream>
#include <stdexcept>

Player::Player(const std::string& username, int startX, int startY)
    : playername(username), x(startX), y(startY) {}

bool Player::checkCollisionWithEnemies() {
    return true; // TODO: dacă se află un alt jucător pe această poziție să nu poată să se mute
}

void Player::moveUp() { y--; }
void Player::moveDown() { y++; }
void Player::moveLeft() { x--; }
void Player::moveRight() { x++; }

void Player::movePlayer(char direction, int maxX, int maxY, const Map& map) {
    int newX = x;
    int newY = y;

    switch (direction) {
    case 'w': newY--; break; // Move up
    case 's': newY++; break; // Move down
    case 'a': newX--; break; // Move left
    case 'd': newX++; break; // Move right
    default: return; // Invalid direction
    }

    // Verifică dacă jucătorul poate să se mute pe noua poziție
    if (canMoveTo(map, newX, newY)) {
        x = newX;
        y = newY;
    }
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

void Player::shoot(Direction direction) {
    weapon.shoot(x, y, direction);
}

std::string Player::getName() const {
    return playername; // Return the player's name
}

Weapon& Player::getWeapon() {
    return weapon;
}

void Player::shoot() {
    // Implement shooting logic here
}

void Player::loseLife() {
    if (lives > 0) {
        lives--;
    }
}

bool Player::isEliminated() const {
    return lives <= 0;
}

bool Player::hasWon() const {
    // Implement winning condition logic here
    return false;
}

std::pair<int, int> Player::getPosition() const {
    return std::make_pair(x, y); // Return the player's current position
}

int Player::getScore() const {
    return score; // Return the player's score
}

int Player::getLives() const {
    return lives; // Return the number of lives left
}

void Player::updateScore(int points) {
    score += points; // Update the player's score
}

void Player::setPlayerName(const std::string& playerName) {
    playername = playerName; // Set the player's name
}
