#pragma once

#include "Bullet.h"
#include <vector>

class Weapon {
private:
    std::vector<Bullet> m_bullets;
    int m_waitTime;
    double m_bulletSpeed;
    int m_powerLevel;

public:
    Weapon(int initialWaitTime = 4, double initialSpeed = 0.25);

    bool canShoot() const;
    void upgradePower();
    int getWaitTime() const;
    double getBulletSpeed() const;

    void modifyWaitTime(int newWaitT);
    void modifyBulletSpeed(double newBulletS);
    void shoot(double startX, double startY, Direction direction);

    void reset();

    std::vector<Bullet>& getBullets();
};
