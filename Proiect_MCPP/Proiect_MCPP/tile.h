#pragma once

enum class TileType {
    EMPTY,
    WALL,
    DESTRUCTIBLE_WALL
};

class Tile {
private:
    TileType m_type;
    bool m_wasJustDestroyed;

public:
    Tile(TileType type = TileType::EMPTY);

    bool isWalkable() const;
    void destroy();
    bool isDestructible() const;
    TileType getType() const;
    void setType(TileType type);
    void vacate();

    bool wasJustDestroyed() const;
    void resetDestroyedFlag();
};