#include "Client.h"
#include <iostream>
#include <string>

int main() {
    Client client("http://localhost:8080");

    std::string username, password;
    std::cout << "Introduceți username: ";
    std::cin >> username;
    std::cout << "Introduceți parola: ";
    std::cin >> password;

    cpr::Response response = client.registerUser(username, password);

    if (response.status_code == 201) {
        std::cout << "Înregistrare reușită!" << std::endl;
    }
    else {
        std::cout << "Înregistrare eșuată!" << std::endl;
    }

    return 0;
}

//PROBA PENTRU BAZA DE DATE


//MAIN FOLOSIT LA REFACEREA BACKENDULUI
//#include "PlayerDisplay.h"
//#include "MapDisplay.h"
//#include "BulletDisplay.h"
//#include "BombDisplay.h"
//#include "PowerUpDisplay.h"
//#include <SFML/Graphics.hpp>
//#include <iostream>
//
//int main() {
//    // Game configuration
//    const int mapWidth = 10;
//    const int mapHeight = 10;
//    const float tileSize = 80.0f;
//
//    // Create game map
//    Map gameMap(mapWidth, mapHeight);
//
//    // Create players
//    Player player1(0, 0, 0);
//    Player player2(1, mapWidth - 1, mapHeight - 1);
//    gameMap.addPlayer(player1);
//    gameMap.addPlayer(player2);
//
//    // Create displays
//    TileDisplay tileDisplay;
//    MapDisplay mapDisplay(gameMap, tileDisplay);
//
//    // Player displays
//    std::map<int, PlayerDisplay> playerDisplays = {
//        {0, PlayerDisplay(&player1, "../assets/pl")},
//        {1, PlayerDisplay(&player2, "../assets/pl")}
//    };
//
//    // Create window
//    sf::RenderWindow window(
//        sf::VideoMode(mapWidth * tileSize, mapHeight * tileSize),
//        "Bomberman Game"
//    );
//    window.setFramerateLimit(60);
//
//    // Clocks and timers
//    sf::Clock gameClock;
//    sf::Clock movementClock1, movementClock2;
//    sf::Clock shootClock1, shootClock2;
//
//    // Movement and shooting constants
//    const float movementCooldown = 0.2f;
//    const float shootCooldown = 0.5f;
//
//    // Display management
//    std::vector<BulletDisplay> bulletDisplays;
//    std::vector<BombDisplay> bombDisplays;
//    std::vector<PowerUpDisplay> powerUpDisplays;
//
//    // Main game loop
//    while (window.isOpen()) {
//        // Event handling
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        // Time management
//        float deltaTime = gameClock.restart().asSeconds();
//        deltaTime = std::min(deltaTime, 0.1f);
//
//        // Game state updates
//        gameMap.updateBombs(deltaTime);
//        gameMap.updateBullets(deltaTime);
//        gameMap.updatePowerUps(deltaTime);
//
//        // Player references
//        auto& players = gameMap.getPlayers();
//        auto player1It = std::find_if(players.begin(), players.end(),
//            [](const Player& p) { return p.getId() == 0; });
//        auto player2It = std::find_if(players.begin(), players.end(),
//            [](const Player& p) { return p.getId() == 1; });
//
//        for (auto& player : gameMap.getPlayers()) {
//            player.updatePowerUps(deltaTime);
//        }
//
//        // Modify the power-up collection to provide more feedback
//        for (auto& player : gameMap.getPlayers()) {
//            gameMap.collectPowerUps(player);
//
//            // Optional: Add some debug output
//            if (player.hasShield()) {
//                std::cout << "Player " << player.getId() << " has shield" << std::endl;
//            }
//            if (player.isSpeedBoosted()) {
//                std::cout << "Player " << player.getId() << " is speed boosted" << std::endl;
//            }
//        }
//
//        // Player 1 Movement (WASD)
//        if (player1It != players.end()) {
//            // Get the current move cooldown for the player
//            float moveCooldown = player1It->getMoveCooldown();
//
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
//                player1It->setLastDirection(Direction::UP);
//                // Use player's last move time to respect cooldown
//                if (movementClock1.getElapsedTime().asSeconds() >= moveCooldown) {
//                    if (gameMap.movePlayer(player1It->getId(), 0, -1, deltaTime)) {
//                        movementClock1.restart();
//                    }
//                }
//            }
//            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
//                player1It->setLastDirection(Direction::DOWN);
//                if (movementClock1.getElapsedTime().asSeconds() >= moveCooldown) {
//                    if (gameMap.movePlayer(player1It->getId(), 0, 1, deltaTime)) {
//                        movementClock1.restart();
//                    }
//                }
//            }
//            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
//                player1It->setLastDirection(Direction::LEFT);
//                if (movementClock1.getElapsedTime().asSeconds() >= moveCooldown) {
//                    if (gameMap.movePlayer(player1It->getId(), -1, 0, deltaTime)) {
//                        movementClock1.restart();
//                    }
//                }
//            }
//            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
//                player1It->setLastDirection(Direction::RIGHT);
//                if (movementClock1.getElapsedTime().asSeconds() >= moveCooldown) {
//                    if (gameMap.movePlayer(player1It->getId(), 1, 0, deltaTime)) {
//                        movementClock1.restart();
//                    }
//                }
//            }
//        }
//
//        // Do the same for Player 2
//        if (player2It != players.end()) {
//            // Get the current move cooldown for the player
//            float moveCooldown = player2It->getMoveCooldown();
//
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
//                player2It->setLastDirection(Direction::UP);
//                if (movementClock2.getElapsedTime().asSeconds() >= moveCooldown) {
//                    if (gameMap.movePlayer(player2It->getId(), 0, -1, deltaTime)) {
//                        movementClock2.restart();
//                    }
//                }
//            }
//            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
//                player2It->setLastDirection(Direction::DOWN);
//                if (movementClock2.getElapsedTime().asSeconds() >= moveCooldown) {
//                    if (gameMap.movePlayer(player2It->getId(), 0, 1, deltaTime)) {
//                        movementClock2.restart();
//                    }
//                }
//            }
//            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
//                player2It->setLastDirection(Direction::LEFT);
//                if (movementClock2.getElapsedTime().asSeconds() >= moveCooldown) {
//                    if (gameMap.movePlayer(player2It->getId(), -1, 0, deltaTime)) {
//                        movementClock2.restart();
//                    }
//                }
//            }
//            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
//                player2It->setLastDirection(Direction::RIGHT);
//                if (movementClock2.getElapsedTime().asSeconds() >= moveCooldown) {
//                    if (gameMap.movePlayer(player2It->getId(), 1, 0, deltaTime)) {
//                        movementClock2.restart();
//                    }
//                }
//            }
//        }
//
//        // Player 1 Shooting
//        if (player1It != players.end() &&
//            shootClock1.getElapsedTime().asSeconds() >= shootCooldown) {
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
//                gameMap.shootBullet(*player1It);
//                shootClock1.restart();
//            }
//        }
//
//        // Player 2 Shooting
//        if (player2It != players.end() &&
//            shootClock2.getElapsedTime().asSeconds() >= shootCooldown) {
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
//                gameMap.shootBullet(*player2It);
//                shootClock2.restart();
//            }
//        }
//
//        // Remove eliminated players
//        gameMap.removeEliminatedPlayers();
//
//        // Update player displays
//        for (auto& pair : playerDisplays) {
//            auto playerIt = std::find_if(players.begin(), players.end(),
//                [&pair](const Player& p) { return p.getId() == pair.first; });
//
//            if (playerIt != players.end()) {
//                pair.second.updatePlayer(&(*playerIt));
//                pair.second.updateDisplay(deltaTime);
//            }
//        }
//        // Collect power-ups for each player
//        for (auto& player : players) {
//            gameMap.collectPowerUps(player);
//        }
//
//        // Recreate displays
//        bulletDisplays.clear();
//        for (auto& bullet : gameMap.getBullets()) {
//            bulletDisplays.emplace_back(&bullet);
//        }
//
//        // Only recreate displays if the number of bombs has changed
//        if (bombDisplays.size() != gameMap.getBombs().size()) {
//            bombDisplays.clear();
//            for (auto& bomb : gameMap.getBombs()) {
//                bombDisplays.emplace_back(&bomb);
//            }
//        }
//
//        // Recreate power-up displays
//        powerUpDisplays.clear();
//        for (auto& powerUp : gameMap.getPowerUps()) {
//            powerUpDisplays.emplace_back(&powerUp);
//        }
//
//        // Rendering
//        window.clear(sf::Color::Black);
//
//        // Draw map and elements
//        mapDisplay.draw(window);
//
//        // Draw players
//        for (auto& pair : playerDisplays) {
//            auto playerIt = std::find_if(players.begin(), players.end(),
//                [&pair](const Player& p) { return p.getId() == pair.first; });
//
//            if (playerIt != players.end()) {
//                pair.second.render(window);
//            }
//        }
//
//        // Tile destruction and bomb spawning
//        for (int y = 0; y < mapHeight; ++y) {
//            for (int x = 0; x < mapWidth; ++x) {
//                Tile& tile = gameMap.getTile(x, y);
//                if (tile.isDestructible() && tile.wasJustDestroyed()) {
//                    gameMap.spawnBombOnDestruction(x, y);
//                    tile.resetDestroyedFlag();
//                }
//            }
//        }
//        // Render bullets
//        for (auto& bulletDisplay : bulletDisplays) {
//            bulletDisplay.render(window);
//        }
//
//        // Render bombs
//        for (auto& bombDisplay : bombDisplays) {
//            bombDisplay.render(window, deltaTime);
//        }
//
//        // Render power-ups
//        for (auto& powerUpDisplay : powerUpDisplays) {
//            powerUpDisplay.render(window);
//        }
//
//        // Display the contents of the window
//        window.display();
//    }
//
//    return 0;
//}