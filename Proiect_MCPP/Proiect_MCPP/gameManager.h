#pragma once

class GameManager {
private:
	Map gameMap;
	std::vector<Player> players;
	bool isRunning;

public:
	GameManager();
	void initializeGame();
	void startGame();
	void gameLoop();
	void endGame();
};