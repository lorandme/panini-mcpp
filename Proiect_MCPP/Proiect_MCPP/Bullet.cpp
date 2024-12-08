#include "Bullet.h"

Bullet::Bullet(double startX, double startY, Direction dir, double speed)
    : m_x(startX), m_y(startY), m_direction(dir), m_speed(speed), m_isActive(true) {}

void Bullet::move(double deltaTime) {
    if (m_isActive) {
        switch (m_direction) {
        case Direction::UP:
            m_y -= m_speed * deltaTime;
            break;
        case Direction::DOWN:
            m_y += m_speed * deltaTime;
            break;
        case Direction::LEFT:
            m_x -= m_speed * deltaTime;
            break;
        case Direction::RIGHT:
            m_x += m_speed * deltaTime;
            break;
        }
    }
}

void Bullet::deactivate() {
    m_isActive = false;
}

bool Bullet::checkCollision(int targetX, int targetY) const {
    return m_x == targetX && m_y == targetY;
}

std::pair<double, double> Bullet::getPosition() const {
    return { m_x, m_y };
}

bool Bullet::isBulletActive() const {
    return m_isActive;
}

void Bullet::setPosition(double newX, double newY) {
    m_x = newX;  
    m_y = newY;  
}

void Bullet::setDirection(Direction newDirection) {
    m_direction = newDirection;  
}
