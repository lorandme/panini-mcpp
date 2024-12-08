#pragma once

#include <utility>

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Bullet {
private:
    double m_x, m_y;
    Direction m_direction;
    double m_speed;
    bool m_isActive;

public:
    Bullet(double startX, double startY, Direction dir, double speed);

    void move(double deltaTime);
    void deactivate();
    bool checkCollision(int targetX, int targetY) const;

    std::pair<double, double> getPosition() const;
    bool isBulletActive() const;

    void setPosition(double newX, double newY);  
    void setDirection(Direction newDirection);
};
