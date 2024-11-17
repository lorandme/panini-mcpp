#pragma once

#include <string>;
#include <vector>;
#include <iostream>;
#include <unordered_map>;


class Account {
private:
    std::string username;
    int points;
    int score;
    std::vector<std::string> purchasedUpgrades;
public:
    Account(const std::string& playerName);

    void addPoints(int points);
    void addWin();
    bool purchaseUpgrade(const std::string& upgrade, int cost);


    void displayStatus() const;

    // Getteri
    const std::string& getName() const;
    int getPoints() const;
    int getScore() const;
    const std::vector<std::string>& getPurchasedUpgrades() const;


};