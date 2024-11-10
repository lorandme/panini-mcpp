#pragma once

enum class TileType {
    EMPTY,
    WALL,
    DESTRUCTIBLE_WALL,
    BOMB
};

class Tile {
private:
	TileType type;
public:
    Tile();
    Tile(TileType type);
    bool isOccupied() const;
    void destroy();

    TileType getType() const;
	void setType(TileType type);
    void setBomb();
};
