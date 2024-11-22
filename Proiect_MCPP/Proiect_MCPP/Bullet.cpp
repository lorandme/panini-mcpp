#include "Bullet.h"

Bullet::Bullet(double startX, double startY, Direction dir, double speed): 
    x(startX), 
    y(startY),
    direction(dir),
    speed(speed),
    isActive(true){}

void Bullet::move(double deltaTime) {
    if (!isActive) return;

    double distance = speed * deltaTime;

    switch (direction) {
    case Direction::UP:
        y -= distance;
        break;
    case Direction::DOWN:
        y += distance;
        break;
    case Direction::LEFT:
        x -= distance;
        break;
    case Direction::RIGHT:
        x += distance;
        break;
    }
}

void Bullet::deactivate() {
    isActive = false;
}

std::pair<double, double> Bullet::getPosition() const {
    return { x, y };
}

bool Bullet::isBulletActive() const {
    return isActive;
}

void Bullet::setPosition(double newX, double newY) {
    x = newX;
    y = newY;
}

void Bullet::setDirection(Direction newDirection) {
    direction = newDirection;
}

bool Bullet::checkCollision(int targetX, int targetY) const {
    return (static_cast<int>(x) == targetX && static_cast<int>(y) == targetY);
}