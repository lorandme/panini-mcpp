#include "weapon.h"
#include "map.h"
#include "account.h"
#include "player.h"

Player::Player(const std::string& username, int startX, int startY)
    : playername(username), x(startX), y(startY){}


bool Player::checkCollisionWithEnemies(){
    return true;
	//TODO: daca se afla un alt jucator pe aceasta pozitie sa nu poata sa se mute
}

void Player::moveUp() { y--; }
void Player::moveDown() { y++; }
void Player::moveLeft() { x--; }
void Player::moveRight() { x++; }

void Player::movePlayer(Player& player, char direction, int maxX, int maxY) {
    switch (direction) {
    case 'w': if (player.y > 0) player.moveUp(); break;         
    case 's': if (player.y < maxY - 1) player.moveDown(); break; 
    case 'a': if (player.x > 0) player.moveLeft(); break;        
    case 'd': if (player.x < maxX - 1) player.moveRight(); break; 
    default: break;
    }
}

