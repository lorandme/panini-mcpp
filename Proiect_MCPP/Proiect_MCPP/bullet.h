#pragma once
#include <utility>
#include "Direction.h"

class Bullet {
private:
    static constexpr double BASE_SPEED = 10.0;
    double m_x, m_y;
    Direction m_direction;
    double m_speed;
    bool m_isActive;
    int m_ownerId;

public:
    Bullet(double startX, double startY, Direction dir, int ownerId);

    Direction getDirection() const { return m_direction; }
    int getOwner() const { return m_ownerId; }

    void move(double deltaTime);
    void deactivate();
    bool checkCollision(int targetX, int targetY) const;

    std::pair<double, double> getPosition() const;
    bool isBulletActive() const;

    void setPosition(double newX, double newY);
    void setDirection(Direction newDirection);
};