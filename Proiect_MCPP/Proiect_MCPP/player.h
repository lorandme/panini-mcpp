#pragma once
#include <string>
#include "account.h"
#include "map.h"
#include "weapon.h"

//fiecare jucator are un cont cu un username unic, dar cand intra in joc va avea un playername introdus de el
class Player {
private:
	std::string playername;
    int x;
    int y;
    int lives=3;
    int score=0;

    bool checkCollisionWithEnemies();

    // Verifică dacă jucătorul poate să se mute pe o anumită poziție pe hartă
    bool canMoveTo(const Map& map, int newX, int newY) const;

public:
	Player(const std::string& name, int startX, int startY);

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void movePlayer(Player& player, char direction, int maxX, int maxY, const Map& map);

    void handleInput(Player& player);

    void shoot(Weapon& weapon, Direction direction);

    //doar pentru testare
    void displayPosition() {
        std::cout << "Player position: (" << x << ", " << y << ")\n";
    }

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