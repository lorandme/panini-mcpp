#include "Bullet.h"
#include <iostream>

Bullet::Bullet(double startX, double startY, Direction dir, int ownerId)
    : m_x(startX), m_y(startY),
    m_direction(dir),
    m_speed(BASE_SPEED),
    m_isActive(true),
    m_ownerId(ownerId),
    m_lifetime(0.0) {
}

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

        m_lifetime += deltaTime;
        if (m_lifetime >= MAX_LIFETIME) {
            deactivate();
        }
    }
}

void Bullet::deactivate() {
    m_isActive = false;
}

bool Bullet::checkCollision(int targetX, int targetY) const {
    const double epsilon = 0.7;
    double dx = std::abs(m_x - targetX);
    double dy = std::abs(m_y - targetY);
    return dx < epsilon && dy < epsilon;
}


std::pair<double, double> Bullet::getPosition() const {
    return { m_x, m_y };
}

bool Bullet::isBulletActive() const {
    return m_isActive;
}

double Bullet::getLifetime() const {
    return m_lifetime;
}

void Bullet::setPosition(double newX, double newY) {
    m_x = newX;
    m_y = newY;
}

void Bullet::setDirection(Direction newDirection) {
    m_direction = newDirection;
}

