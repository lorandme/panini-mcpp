#include "weapon.h"
#include "map.h"
#include "account.h"
#include "player.h"

Player::Player(const std::string& username, int startX, int startY, int initialLives, int initialScore)
    : Account(username), playername(username), x(startX), y(startY), lives(initialLives), score(initialScore) {}


bool Player::checkCollisionWithEnemies(){
	//TODO: daca se afla un alt jucator pe aceasta pozitie sa nu poata sa se mute
}

//TODO: de implementat
void Player::moveUp() {
}

void Player::moveDown() {
}

void Player::moveLeft() {
}

void Player::moveRight() {
}