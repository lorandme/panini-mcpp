#include "Account.h"

Account::Account(const std::string& playerName)
    : m_username(playerName), m_points(0), m_score(0)
{
}

void Account::addPoints(int points)
{
    m_points += points;
}

void Account::addWin()
{
    m_score += 1;
}

bool Account::purchaseUpgrade(const std::string& upgrade, int cost)
{
    if (m_points >= cost) {
        m_points -= cost;
        m_purchasedUpgrades.push_back(upgrade);
        return true;
    }
    return false;
}

void Account::displayStatus() const
{
}

const std::string& Account::getName() const
{
    return m_username;
}

int Account::getPoints() const
{
    return m_points;
}

int Account::getScore() const
{
    return m_score;
}

const std::vector<std::string>& Account::getPurchasedUpgrades() const
{
    return m_purchasedUpgrades;
}
