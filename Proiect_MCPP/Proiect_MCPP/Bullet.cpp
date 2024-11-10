#include "bullet.h"

Bullet::Bullet(double startX, double startY, Direction dir, double speed)
	: x(startX), y(startY), direction(dir), speed(speed),isActive(true){}

// Glontul se deplaseaza ihn directia specificata
void Bullet::move(double deltaTime) {
	if (!isActive)
		return;
	double distance = speed * deltaTime;

    switch (direction) {
    case Direction::UP:
        y -= distance;
        break;
    case Direction::DOWN:
        y += distance;
        break;
    case Direction::LEFT:
        x -= distance;
        break;
    case Direction::RIGHT:
        x += distance;
        break;
    }
}

// Se dezactiveaza glontul
void Bullet::deactivate() {
	isActive = false;
}

// Se returneaza pozitia glontului
std::pair<double, double> Bullet::getPosition() const {
	return { x,y };
}

// Se verifica daca glontul este activ
bool Bullet::isBulletActive() const {
	return isActive;
}

// Seteaza o pozitie noua pentru glont
void Bullet::setPosition(double newX, double newY) {
	x = newX;
	y = newY;
}

//Seteaza o noua directie pentru glont
void Bullet::setDirection(Direction newDir) {
	direction = newDir;
}
