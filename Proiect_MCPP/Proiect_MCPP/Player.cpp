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

void Player::movePlayer(Player& player, char direction, int maxX, int maxY, const Map& map) {

    int newX = x;
    int newY = y;

    switch (direction) {
    case 'w': if (player.y > 0) player.moveUp(); break;
    case 's': if (player.y < maxY - 1) player.moveDown(); break;
    case 'a': if (player.x > 0) player.moveLeft(); break;
    case 'd': if (player.x < maxX - 1) player.moveRight(); break;
    default: break;
    }

    // Verifică dacă jucătorul poate să se mute pe noua poziție
    if (canMoveTo(map, newX, newY)) {
        x = newX;
        y = newY;
    }
}

    bool Player::canMoveTo(const Map & map, int newX, int newY) const {
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

void Player::shoot(Weapon& weapon, Direction direction) {
	weapon.shoot(x, y, direction);
}


