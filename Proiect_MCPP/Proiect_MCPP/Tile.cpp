#include "tile.h"
#include <iostream>


Tile::Tile() : type(TileType::EMPTY) {}
Tile::Tile(TileType type) : type(type) {}

bool Tile::isOccupied() const {
	return type != TileType::EMPTY;
}

void Tile::destroy() {
	if (type == TileType::DESTRUCTIBLE_WALL)
		type = TileType::EMPTY;
}

TileType Tile::getType() const {
	return type;
}

void Tile::setType(TileType type) {
	this->type = type;
}

void Tile::setBomb() {
	type = TileType::BOMB;
}