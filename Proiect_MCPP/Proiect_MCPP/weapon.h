#pragma once
#include "bullet.h"
#include <vector>

class Weapon {
private:
	std::vector<Bullet> bullets;
	int waitTime;
	double bulletSpeed;
	int powerLevel;

public:
	//Constructor
	Weapon(int initialWaitTime = 4, double initialSpeed = 0.25);

	//Metode

	bool canShoot() const;
	void upgradePower();
	int getWaitTime() const;
	double getBulletSpeed() const;

	void modifyWaitTime(int newWaitT);
	void modifyBulletSpeed(double newBulletS);
	void shoot(double startX, double startY, Direction direction);

	//Se va reveni la setarile initiale
	void reset();

	//Getteri

	std::vector<Bullet>& getBullets();
	void shoot(double startX, double startY, Direction direction);


};
