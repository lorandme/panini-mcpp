#pragma once
#include <utility>

class Bomb {
private:
    std::pair<int, int> m_position;
    int m_owner;
    float m_timer;
    bool m_exploded;
    const float m_explosionTime = 2.0f;
    bool m_damageDone = false;
    float m_timeSinceExplosion = 0.0f;

public:
    float getMaxTimer() const { return m_explosionTime; }
    Bomb(int x, int y, int owner);
    Bomb(const Bomb& other);
    Bomb& operator=(const Bomb& other);
    Bomb(Bomb&& other) noexcept;
    Bomb& operator=(Bomb&& other) noexcept;

    void update(float deltaTime);

    std::pair<int, int> getPosition() const;
    int getX() const;
    int getY() const;
    bool isExploded() const;
    bool isAboutToExplode() const;
    float getTimer() const { return m_timer; }
    bool hasDamageDone() const { return m_damageDone; }
    void setDamageDone(bool done) { m_damageDone = done; }
    float getExplosionTime() const { return m_explosionTime; }
    float getTimeSinceExplosion() const { return m_timeSinceExplosion; }
};