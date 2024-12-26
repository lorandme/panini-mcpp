#include "Tile.h"
#include "Player.h"

Tile::Tile() : m_type(TileType::EMPTY), m_occupantPlayer(nullptr) {}

Tile::Tile(TileType type) : m_type(type), m_occupantPlayer(nullptr) {}

bool Tile::isOccupied() const {
    return m_occupantPlayer != nullptr;
}

bool Tile::isOccupiedByPlayer() const {
    return m_occupantPlayer != nullptr;
}

bool Tile::isOccupiedByProjectile() const {
    return false; 
}

void Tile::occupyPlayer(std::shared_ptr<Player> player) {
    m_occupantPlayer = player;
}

void Tile::vacate() {
    m_occupantPlayer = nullptr;
}

void Tile::destroy() {
    if (isDestructible()) {
        m_type = TileType::EMPTY;
    }
}

bool Tile::isDestructible() const {
    return m_type == TileType::DESTRUCTIBLE_WALL;
}

TileType Tile::getType() const {
    return m_type;
}

void Tile::setType(TileType newType) {
    m_type = newType;
}

void Tile::setBomb() {
    m_type = TileType::BOMB;
}
