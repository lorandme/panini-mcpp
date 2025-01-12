#ifndef POWERUP_H
#define POWERUP_H

#include <string>
#include <random>
#include "Tile.h"


class PowerUp {
public:
    enum Type {
        EXTRA_HP,
        SHIELD,
        SPEED_BOOST
    };

    PowerUp(int x, int y, Type type);

    int getX() const;
    int getY() const;
    Type getType() const;
    std::string getTypeName() const;

    static PowerUp generateRandom(int maxX, int maxY, const std::vector<std::vector<Tile>>& map);

private:
    int x, y;
    Type type;
};

#endif // POWERUP_H

