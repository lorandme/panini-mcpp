#pragma once
#include <string>
class Player {
private:
    std::string username;
    int x;
    int y;
    int lives;
    int score;

    void checkCollisionWithEnemies();

public:
    Player(const std::string& username, int initialX, int initialY);

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
};