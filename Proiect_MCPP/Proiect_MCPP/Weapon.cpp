#include "Weapon.h"
#include "Bullet.h"
#include <iostream>

Weapon::Weapon(int initialWaitTime, double initialSpeed)
    : m_waitTime(initialWaitTime), m_bulletSpeed(initialSpeed), m_powerLevel(1) {}

bool Weapon::canShoot() const {
    return true;
}

void Weapon::upgradePower() {
    if (m_powerLevel < 4) { // There are 4 power levels
        m_waitTime = m_waitTime / 2;
        m_powerLevel++;
        std::cout << "Upgraded weapon! New wait time: " << m_waitTime << " seconds.\n";
    }
    else {
        std::cout << "Maximum power level already reached.\n";
    }
}

int Weapon::getWaitTime() const {
    return m_waitTime;
}

double Weapon::getBulletSpeed() const {
    return m_bulletSpeed;
}

void Weapon::modifyWaitTime(int newWaitTime) {
    m_waitTime = newWaitTime;
}

void Weapon::modifyBulletSpeed(double newBulletSpeed) {
    m_bulletSpeed = newBulletSpeed;
}

void Weapon::reset() {
    m_waitTime = 4;
    m_bulletSpeed = 0.25;
    m_powerLevel = 1;
    std::cout << "Weapon returned to original state.\n";
}

void Weapon::shoot(double startX, double startY, Direction direction) {
    if (canShoot()) {
        Bullet newBullet(startX, startY, direction, m_bulletSpeed);
        m_bullets.push_back(newBullet);
    }
}

std::vector<Bullet>& Weapon::getBullets() {
    return m_bullets;
}
