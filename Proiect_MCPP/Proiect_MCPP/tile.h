#pragma once

#include <optional>  
#include <memory>    

enum class TileType {
    EMPTY,
    WALL,
    DESTRUCTIBLE_WALL,
    BOMB,
    POWERUP
};

class Player;
class Projectile;

class Tile {
private:
    TileType m_type;
    std::shared_ptr<Player> m_occupantPlayer;

public:
    Tile();
    Tile(TileType type);

    bool isOccupied() const;
    bool isOccupiedByPlayer() const;
    bool isOccupiedByProjectile() const;
    void occupyPlayer(std::shared_ptr<Player> player);
    void vacate();

    void destroy();
    bool isDestructible() const;

    TileType getType() const;
    void setType(TileType type);

    void setBomb();
};
