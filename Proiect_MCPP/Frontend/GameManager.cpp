#include "GameManager.h"
#include <iostream>
#include <algorithm>

GameManager::GameManager(int mapWidth, int mapHeight, float tileSize)
    : mapWidth(mapWidth)
    , mapHeight(mapHeight)
    , tileSize(tileSize)
    , gameMap(mapWidth, mapHeight)
    , mapDisplay(gameMap, tileDisplay)
    , window(sf::VideoMode(mapWidth* tileSize, mapHeight* tileSize), "Wizard War")
{
    Player player1(0, 0, 0);
    Player player2(1, mapWidth - 1, 0);
    Player player3(2, 0, mapHeight - 1);
    Player player4(3, mapWidth - 1, mapHeight - 1);
    gameMap.addPlayer(player1);
    gameMap.addPlayer(player2);
    gameMap.addPlayer(player3);
    gameMap.addPlayer(player4);

    playerDisplays = {
        {0, PlayerDisplay(&player1, "../assets/pl")},
        {1, PlayerDisplay(&player2, "../assets/pl")},
        {2, PlayerDisplay(&player2, "../assets/pl")},
        {3, PlayerDisplay(&player2, "../assets/pl")}
    };
    window.setFramerateLimit(60);
}

void GameManager::run() {
    while (window.isOpen()) {
        handleEvents();

        float deltaTime = gameClock.restart().asSeconds();
        deltaTime = std::min(deltaTime, 0.1f);

        updateGame(deltaTime);

        if (gameMap.getPlayers().empty()) {
            break;
        }

        updateDisplays(deltaTime);
        render();
    }
}

void GameManager::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void GameManager::updateGame(float deltaTime) {
    gameMap.updateBombs(deltaTime);
    gameMap.updateBullets(deltaTime);
    gameMap.updatePowerUps(deltaTime);

    for (auto& player : gameMap.getPlayers()) {
        player.updatePowerUps(deltaTime);
    }

    for (auto& player : gameMap.getPlayers()) {
        gameMap.collectPowerUps(player);
    }

    handlePlayerMovement(deltaTime);
    handlePlayerShooting();

    gameMap.removeEliminatedPlayers();

    checkGameOver();
}

void GameManager::checkGameOver() {
    auto& players = gameMap.getPlayers();

    if (players.size() <= 1) {
        endGame();
    }
}

void GameManager::endGame() {
    auto& players = gameMap.getPlayers();

    if (players.empty()) {
        displayGameOverScreen("Draw! No players remain.");
    }
    else if (players.size() == 1) {
        auto& winner = players[0];

        winner.addScore(10);

        std::string winnerText = "Player " + std::to_string(winner.getId() + 1) +
            " Wins! Score: " + std::to_string(winner.getScore());
        displayGameOverScreen(winnerText);
    }
}

void GameManager::displayGameOverScreen(const std::string& message) {
    sf::Font font;
    if (!font.loadFromFile("../assets/Arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return;
    }

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString(message);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::White);

    sf::FloatRect textBounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(textBounds.left + textBounds.width / 2.0f,
        textBounds.top + textBounds.height / 2.0f);
    gameOverText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    window.clear(sf::Color::Black);
    window.draw(gameOverText);
    window.display();

    sf::Clock waitClock;
    bool keepOpen = true;
    while (keepOpen) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                event.type == sf::Event::KeyPressed ||
                waitClock.getElapsedTime().asSeconds() >= 5.0f) {
                keepOpen = false;
            }
        }
    }

    window.close();
}

void GameManager::handlePlayerMovement(float deltaTime) {
    auto& players = gameMap.getPlayers();
    auto player1It = std::find_if(players.begin(), players.end(),
        [](const Player& p) { return p.getId() == 0; });
    auto player2It = std::find_if(players.begin(), players.end(),
        [](const Player& p) { return p.getId() == 1; });

    if (player1It != players.end()) {
        float moveCooldown = player1It->getMoveCooldown();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player1It->setLastDirection(Direction::UP);
            if (movementClock1.getElapsedTime().asSeconds() >= moveCooldown) {
                if (gameMap.movePlayer(player1It->getId(), 0, -1, deltaTime)) {
                    movementClock1.restart();
                }
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player1It->setLastDirection(Direction::DOWN);
            if (movementClock1.getElapsedTime().asSeconds() >= moveCooldown) {
                if (gameMap.movePlayer(player1It->getId(), 0, 1, deltaTime)) {
                    movementClock1.restart();
                }
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player1It->setLastDirection(Direction::LEFT);
            if (movementClock1.getElapsedTime().asSeconds() >= moveCooldown) {
                if (gameMap.movePlayer(player1It->getId(), -1, 0, deltaTime)) {
                    movementClock1.restart();
                }
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player1It->setLastDirection(Direction::RIGHT);
            if (movementClock1.getElapsedTime().asSeconds() >= moveCooldown) {
                if (gameMap.movePlayer(player1It->getId(), 1, 0, deltaTime)) {
                    movementClock1.restart();
                }
            }
        }
    }

    if (player2It != players.end()) {
        float moveCooldown = player2It->getMoveCooldown();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            player2It->setLastDirection(Direction::UP);
            if (movementClock2.getElapsedTime().asSeconds() >= moveCooldown) {
                if (gameMap.movePlayer(player2It->getId(), 0, -1, deltaTime)) {
                    movementClock2.restart();
                }
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            player2It->setLastDirection(Direction::DOWN);
            if (movementClock2.getElapsedTime().asSeconds() >= moveCooldown) {
                if (gameMap.movePlayer(player2It->getId(), 0, 1, deltaTime)) {
                    movementClock2.restart();
                }
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player2It->setLastDirection(Direction::LEFT);
            if (movementClock2.getElapsedTime().asSeconds() >= moveCooldown) {
                if (gameMap.movePlayer(player2It->getId(), -1, 0, deltaTime)) {
                    movementClock2.restart();
                }
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player2It->setLastDirection(Direction::RIGHT);
            if (movementClock2.getElapsedTime().asSeconds() >= moveCooldown) {
                if (gameMap.movePlayer(player2It->getId(), 1, 0, deltaTime)) {
                    movementClock2.restart();
                }
            }
        }
    }
}

void GameManager::handlePlayerShooting() {
    auto& players = gameMap.getPlayers();
    auto player1It = std::find_if(players.begin(), players.end(),
        [](const Player& p) { return p.getId() == 0; });
    auto player2It = std::find_if(players.begin(), players.end(),
        [](const Player& p) { return p.getId() == 1; });

    if (player1It != players.end() && shootClock1.getElapsedTime().asSeconds() >= shootCooldown) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            gameMap.shootBullet(*player1It);
            shootClock1.restart();
        }
    }

    if (player2It != players.end() && shootClock2.getElapsedTime().asSeconds() >= shootCooldown) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
            gameMap.shootBullet(*player2It);
            shootClock2.restart();
        }
    }
}

void GameManager::updateDisplays(float deltaTime) {
    auto& players = gameMap.getPlayers();

    for (auto& pair : playerDisplays) {
        auto playerIt = std::find_if(players.begin(), players.end(),
            [&pair](const Player& p) { return p.getId() == pair.first; });

        if (playerIt != players.end()) {
            pair.second.updatePlayer(&(*playerIt));
            pair.second.updateDisplay(deltaTime);
        }
    }

    bulletDisplays.clear();
    for (auto& bullet : gameMap.getBullets()) {
        bulletDisplays.emplace_back(&bullet);
    }

    if (bombDisplays.size() != gameMap.getBombs().size()) {
        bombDisplays.clear();
        for (auto& bomb : gameMap.getBombs()) {
            bombDisplays.emplace_back(&bomb);
        }
    }

    powerUpDisplays.clear();
    for (auto& powerUp : gameMap.getPowerUps()) {
        powerUpDisplays.emplace_back(&powerUp);
    }
}

void GameManager::render() {
    window.clear(sf::Color::Black);

    mapDisplay.draw(window);

    for (auto& pair : playerDisplays) {
        auto playerIt = std::find_if(gameMap.getPlayers().begin(), gameMap.getPlayers().end(),
            [&pair](const Player& p) { return p.getId() == pair.first; });

        if (playerIt != gameMap.getPlayers().end()) {
            pair.second.render(window);
        }
    }

    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            Tile& tile = gameMap.getTile(x, y);
            if (tile.isDestructible() && tile.wasJustDestroyed()) {
                gameMap.spawnBombOnDestruction(x, y);
                tile.resetDestroyedFlag();
            }
        }
    }

    for (auto& bulletDisplay : bulletDisplays) {
        bulletDisplay.render(window);
    }

    for (auto& bombDisplay : bombDisplays) {
        bombDisplay.render(window, gameClock.getElapsedTime().asSeconds());
    }

    for (auto& powerUpDisplay : powerUpDisplays) {
        powerUpDisplay.render(window);
    }

    sf::Font font;
    if (font.loadFromFile("../assets/Arial.ttf")) {
        for (const auto& pair : playerDisplays) {
            auto playerIt = std::find_if(gameMap.getPlayers().begin(), gameMap.getPlayers().end(),
                [&pair](const Player& p) { return p.getId() == pair.first; });

            if (playerIt != gameMap.getPlayers().end()) {
                sf::Text scoreText;
                scoreText.setFont(font);
                scoreText.setCharacterSize(20);
                scoreText.setFillColor(sf::Color::White);

                float xPos = (pair.first == 0) ? 10 :
                    (pair.first == 1) ? window.getSize().x - 100 :
                    (pair.first == 2) ? 10 :
                    window.getSize().x - 100;

                float yPos = (pair.first < 2) ? 10 : window.getSize().y - 50;

                scoreText.setPosition(xPos, yPos);

                scoreText.setString("Player " + std::to_string(pair.first + 1) +
                    "\nScore: " + std::to_string(playerIt->getScore()));

                window.draw(scoreText);
            }
        }
    }

    window.display();
}