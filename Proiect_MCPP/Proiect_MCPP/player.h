#pragma once

#include <string>
#include "account.h"
#include "map.h"
#include "weapon.h"
#include "team.h"

class Team; // Forward declaration
// Fiecare jucător are un cont cu un username unic, dar când intră în joc va avea un playername introdus de el
class Player {
private:
    std::string playername;
    int x;
    int y;
    int lives = 3;
    int score = 0;
    Team* team;

    bool checkCollisionWithEnemies(); // Check for collisions with other players/enemies

    // Verifică dacă jucătorul poate să se mute pe o anumită poziție pe hartă
    bool canMoveTo(const Map& map, int newX, int newY) const;

    Weapon weapon; // Fiecare jucător are o armă

public:
    Player(const std::string& name, int startX, int startY);

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void movePlayer(char direction, int maxX, int maxY, const Map& map);

    void handleInput(); // Handle player input

    void shoot(Direction direction); // Shoot in a specific direction

    // Doar pentru testare
    void displayPosition() const {
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
    std::string getName() const;
    Weapon& getWeapon();

    Team* getTeamName() const; // Obține echipa jucătorului
    void setTeam(Team* newTeam); // Setează echipa jucătorului
};