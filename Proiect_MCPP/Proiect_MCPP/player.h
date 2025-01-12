#pragma once

#include <string>
#include "Account.h"
#include "Map.h"
#include "Weapon.h"
#include "Team.h"

class Team;

class Player {
private:
    std::string m_playername;
    int m_x;
    int m_y;
    int m_lives = 3;
    int m_score = 0;
    Team* m_team;

    bool checkCollisionWithEnemies();
    bool canMoveTo(const Map& map, int newX, int newY) const;

    Weapon m_weapon;

    int m_shieldDuration = 0; // Durata scutului
    bool m_hasShield = false; // Starea scutului

    int m_speedBoostDuration = 0; // Durata creșterii vitezei
    bool m_speedBoosted = false; // Starea de viteză crescută

public:
    Player(const std::string& name, int startX, int startY);

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void movePlayer(char direction, int maxX, int maxY, const Map& map);

    void handleInput();

    void displayPosition() const;

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

    int getX() const { return m_x; }
    int getY() const { return m_y; }

    void addHP(int hp) { m_lives += hp; }

    void activateShield(int duration) { m_shieldDuration = duration; m_hasShield = true; }

    void increaseSpeed(int duration) { m_speedBoostDuration = duration; m_speedBoosted = true; }



};
