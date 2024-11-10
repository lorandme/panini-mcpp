#pragma once
#include <string>
#include "account.h"

//fiecare jucator are un cont cu un username unic, dar cand intra in joc va avea un playername introdus de el
class Player : public Account {
private:
	std::string playername;
    int x;
    int y;
    int lives;
    int score;

    bool checkCollisionWithEnemies();

public:
	Player(const std::string& name, int x, int y, int lives, int score);

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void shoot();
    void loseLife();

    bool isEliminated() const;
    bool hasWon() const;

    std::pair<int, int> getPosition() const;
    int getScore() const;
	int getLives() const;

    void updateScore(int points);

	void setPlayerName(const std::string& playerName);
};