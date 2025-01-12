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

PowerUp PowerUp::generateRandom(int maxX, int maxY, const std::vector<std::vector<Tile>>& map) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distX(0, maxX - 1);
    std::uniform_int_distribution<> distY(0, maxY - 1);
    std::uniform_int_distribution<> typeDist(0, 2);

    int x, y;
    do {
        x = distX(gen);
        y = distY(gen);
    } while (map[y][x].getType() != TileType::EMPTY); // Verifică doar tile-uri libere

    return PowerUp(x, y, static_cast<Type>(typeDist(gen)));
}

