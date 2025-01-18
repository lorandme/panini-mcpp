#pragma once
#include <string>
#include <random>

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

private:
    int x, y;
    Type type;
};