#include "Bomb.h"

Bomb::Bomb(int x, int y, int owner)
    : m_position(x, y), m_owner(owner),
    m_timer(0.0f), m_exploded(false),
    m_explosionTime(3.0f) {
}

Bomb::Bomb(const Bomb& other)
    : m_position(other.m_position),
    m_owner(other.m_owner),
    m_timer(other.m_timer),
    m_exploded(other.m_exploded),
    m_explosionTime(other.m_explosionTime) {
}

Bomb& Bomb::operator=(const Bomb& other) {
    if (this != &other) {
        m_position = other.m_position;
        m_owner = other.m_owner;
        m_timer = other.m_timer;
        m_exploded = other.m_exploded;
    }
    return *this;
}

Bomb::Bomb(Bomb&& other) noexcept
    : m_position(std::move(other.m_position)),
    m_owner(std::move(other.m_owner)),
    m_timer(std::move(other.m_timer)),
    m_exploded(std::move(other.m_exploded)),
    m_explosionTime(other.m_explosionTime) {
}

Bomb& Bomb::operator=(Bomb&& other) noexcept {
    if (this != &other) {
        m_position = std::move(other.m_position);
        m_owner = std::move(other.m_owner);
        m_timer = std::move(other.m_timer);
        m_exploded = std::move(other.m_exploded);
    }
    return *this;
}

void Bomb::update(float deltaTime) {
    if (!m_exploded) {
        m_timer += deltaTime;
        if (m_timer >= m_explosionTime) {
            m_exploded = true;
            m_timer = m_explosionTime;
        }
    }
}

std::pair<int, int> Bomb::getPosition() const {
    return m_position;
}

int Bomb::getX() const {
    return m_position.first;
}

int Bomb::getY() const {
    return m_position.second;
}

bool Bomb::isExploded() const {
    return m_exploded;
}

bool Bomb::isAboutToExplode() const {
    return m_timer >= m_explosionTime - 1.0f;
}