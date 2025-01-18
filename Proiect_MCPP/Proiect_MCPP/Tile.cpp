#include "Tile.h"
#include <iostream> 
Tile::Tile(TileType type) : m_type(type), m_wasJustDestroyed(false) {}

void Tile::vacate() {
}

void Tile::destroy() {
    if (isDestructible()) {
        m_type = TileType::EMPTY;
        m_wasJustDestroyed = true;
        vacate();
    }
}

bool Tile::isDestructible() const {
    return m_type == TileType::DESTRUCTIBLE_WALL;
}

TileType Tile::getType() const {
    return m_type;
}

void Tile::setType(TileType type) {
    m_type = type;
}

bool Tile::isWalkable() const {
    return m_type == TileType::EMPTY;
}

bool Tile::wasJustDestroyed() const {
    return m_wasJustDestroyed;
}

void Tile::resetDestroyedFlag() {
    m_wasJustDestroyed = false;
}