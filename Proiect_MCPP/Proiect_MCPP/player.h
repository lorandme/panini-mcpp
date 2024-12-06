#pragma once

#include <string>
#include "account.h"
#include "Map.h"
#include "Weapon.h"
#include "Team.h"

class Team; // Forward declaration

// Fiecare jucător are un cont cu un username unic, dar când intră în joc va avea un playername introdus de el
class Player {
private:
    std::string m_playername; // Variabila de membru cu prefixul m_
    int m_x;                   // Variabila de membru cu prefixul m_
    int m_y;                   // Variabila de membru cu prefixul m_
    int m_lives = 3;           // Variabila de membru cu prefixul m_
    int m_score = 0;           // Variabila de membru cu prefixul m_
    Team* m_team;              // Variabila de membru cu prefixul m_

    bool checkCollisionWithEnemies(); // Check for collisions with other players/enemies

    bool canMoveTo(const Map& map, int newX, int newY) const;

    Weapon m_weapon; // Variabila de membru cu prefixul m_

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
        std::cout << "Player position: (" << m_x << ", " << m_y << ")\n";
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

    Team* getTeamName() const;
    void setTeam(Team* newTeam);

    void addReward(int points);
};