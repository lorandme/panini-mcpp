export module block;

#include <iostream>

export enum class TileType {
    Empty,
    IndestructibleWall,
    DestructibleWall,
    Bomb
};

export class Tile {
public:
    TileType type;

    Tile(TileType type = TileType::Empty) : type(type) {}

    bool isOccupied() const {
        return type != TileType::Empty;
    }

    void destroy() {
        if (type == TileType::DestructibleWall) {
            type = TileType::Empty;
        }
    }
};
