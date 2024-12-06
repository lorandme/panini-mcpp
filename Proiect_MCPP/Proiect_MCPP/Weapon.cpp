#include "Weapon.h"
#include "Bullet.h"
#include <iostream>

Weapon::Weapon(int initialWaitTime, double initialSpeed)
    : waitTime(initialWaitTime), bulletSpeed(initialSpeed), powerLevel(1) {}

bool Weapon::canShoot() const {

    return true;
}

void Weapon::upgradePower() {
    if (powerLevel < 4) { //Exista 4 trepte de putere
        waitTime = waitTime / 2;
        powerLevel++;
        std::cout << "Upgraded weapon! New wait time: " << waitTime << " seconds.\n";
    }
    else {
        std::cout << "Maximum power level already reached.\n";
    }
}

int Weapon::getWaitTime() const {
    return waitTime;
}

double Weapon::getBulletSpeed() const {
    return bulletSpeed;
}

void Weapon::modifyWaitTime(int newWait) {
    waitTime = newWait;
}

void Weapon::modifyBulletSpeed(double newBulletS) {
    bulletSpeed = newBulletS;
}

void Weapon::reset() {
    waitTime = 4;
    bulletSpeed = 0.25;
    powerLevel = 1;
    std::cout << "Weapon returned to original state.\n";
}

void Weapon::shoot(double startX, double startY, Direction direction) {
    if (canShoot()) {
        Bullet newBullet(startX, startY, direction, bulletSpeed);
        bullets.push_back(newBullet); 
    }
}

std::vector<Bullet>& Weapon::getBullets() {
    return bullets;
}
