export module player;

import <string>;
import account;

export class Player {
public:
	Player(const std::string& playerName);

	//metode miscare
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	//metode pentru atac si upgrade
	void attack();
	bool upgradeWeapon(const std::string& upgradeName, int cost);
	bool upgradeSpeed(int cost);

	//metode pentru statusul jucatorului
	void takeDamage(int damage);
	bool isAlive() const;
	void displayStatus() const;

	//getteri
	int getHealth() const;
	const std::string& getName() const;

private:
	std::string name;
	int health;
	int posX, posY;      
	int bulletSpeed;      
	Account account;
};