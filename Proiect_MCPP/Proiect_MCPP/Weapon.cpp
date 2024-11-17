#include "weapon.h"
#include "bullet.h"
#include <iostream>

Weapon::Weapon(int initialWaitTime, double initialSpeed)
    : waitTime(initialWaitTime), bulletSpeed(initialSpeed), powerLevel(1) {}

//Verificarea posibilitatii de a trage cu arma
bool Weapon::canShoot() const {

    return true;
}

//Actualizarea puterii armei
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
//Getter pentru timpul de asteptare dintre gloante
int Weapon::getWaitTime() const {
    return waitTime;
}

//Getter pentru viteza glontului
double Weapon::getBulletSpeed() const {
    return bulletSpeed;
}

//Modifica timpul de asteptare
void Weapon::modifyWaitTime(int newWait) {
    waitTime = newWait;
}

//Modifica viteza glontului
void Weapon::modifyBulletSpeed(double newBulletS) {
    bulletSpeed = newBulletS;
}

//Reseteaza arma la setarile initiale
void Weapon::reset() {
    waitTime = 4;
    bulletSpeed = 0.25;
    powerLevel = 1;
    std::cout << "Weapon returned to original state.\n";
}

void Weapon::shoot(double startX, double startY, Direction direction) {
    if (canShoot()) {
        Bullet newBullet(startX, startY, direction, bulletSpeed);
        bullets.push_back(newBullet); // Add the bullet to the vector

    }

}