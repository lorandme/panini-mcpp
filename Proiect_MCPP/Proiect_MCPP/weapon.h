#pragma once

class Weapon {
private:
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

	//Se va reveni la setarile initiale
	void reset();

};
