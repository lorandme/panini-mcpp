#include <iostream>

enum class TileType {
    EMPTY,
    WALL,
    DESTRUCTIBE_WALL
};

class Tile {
public:
    TileType type;
    bool hasBomb;
    Tile();

    bool isOccupied() const; /*{
        return type != TileType::EMPTY;
    } #a se implementa intr-un cpp separat*/

    void destroy(); /*{
        if (type == TileType::DESTRUCTIBE_WALL) {
            type = TileType::EMPTY;
        }
    } #a se implementa intr-un cpp separat*/

    TileType getType() const;
};
