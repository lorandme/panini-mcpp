export module account;

import <string>;
import <vector>;
import <iostream>;
import <unordered_map>;


export class Account {
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

private:
    std::string name;
    int points;
    int score;
    std::vector<std::string> purchasedUpgrades;
};