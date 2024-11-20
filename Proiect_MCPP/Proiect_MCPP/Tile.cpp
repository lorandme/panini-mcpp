#include "Tile.h"
#include "Player.h"

Tile::Tile() : type(TileType::EMPTY), occupantPlayer(nullptr) {}

Tile::Tile(TileType type) : type(type), occupantPlayer(nullptr) {}

bool Tile::isOccupied() const {
    return occupantPlayer != nullptr;
}

bool Tile::isOccupiedByPlayer() const {
    return occupantPlayer != nullptr;
}

bool Tile::isOccupiedByProjectile() const {
    return false;
}

void Tile::occupyPlayer(std::shared_ptr<Player> player) {
    occupantPlayer = player;
}

void Tile::vacate() {
    occupantPlayer = nullptr;
}

void Tile::destroy() {
    if (isDestructible()) {
        type = TileType::EMPTY;
    }
}

bool Tile::isDestructible() const {
    return type == TileType::DESTRUCTIBLE_WALL;
}

TileType Tile::getType() const {
    return type;
}

void Tile::setType(TileType newType) {
    type = newType;
}

void Tile::setBomb() {
    type = TileType::BOMB;
    <<<<<< < HEAD
}
=======
}
>>>>>>> origin/main
