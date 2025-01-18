#include "PowerUp.h"

PowerUp::PowerUp(int x, int y, Type type) : x(x), y(y), type(type) {}

int PowerUp::getX() const {
    return x;
}

int PowerUp::getY() const {
    return y;
}

PowerUp::Type PowerUp::getType() const {
    return type;
}

std::string PowerUp::getTypeName() const {
    switch (type) {
    case EXTRA_HP: return "+1 HP";
    case SHIELD: return "Shield";
    case SPEED_BOOST: return "Speed Boost";
    default: return "Unknown";
    }
}