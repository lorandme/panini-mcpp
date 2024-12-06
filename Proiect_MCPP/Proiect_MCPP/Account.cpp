#include "Account.h"

Account::Account(const std::string& playerName)
{
}

void Account::addPoints(int points)
{
}

void Account::addWin()
{
}

bool Account::purchaseUpgrade(const std::string& upgrade, int cost)
{
	return false;
}

void Account::displayStatus() const
{
}

const std::string& Account::getName() const
{
	return Account::username;
}

int Account::getPoints() const
{
	return 0;
}

int Account::getScore() const
{
	return 0;
}

const std::vector<std::string>& Account::getPurchasedUpgrades() const
{
	// TODO: insert return statement here
	std::vector<std::string> temp;
	return temp;
}
