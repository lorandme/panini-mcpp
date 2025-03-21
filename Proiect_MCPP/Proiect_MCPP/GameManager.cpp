﻿//#include "GameManager.h"
//#include "Map.h"
//#include <iostream>
//#include <conio.h>
//#include <windows.h>
//
//GameManager::GameManager() : m_gameMap(10, 10), m_isRunning(false) {}
//
//void GameManager::initializeGame() {
//    m_gameMap = Map(10, 10);
//    m_players.emplace_back(Player("Player1", 0, 0));
//    m_players.emplace_back(Player("Player2", 9, 9));
//    m_isRunning = true;
//
//    // Afișarea hărții după inițializare
//    renderMap();
//}
//
//void GameManager::startGame() {
//    gameLoop();
//    endGame();
//} 
//
//void GameManager::detectCollisions() {
//    for (auto& player : m_players) {
//        for (auto& bullet : player.getWeapon().getBullets()) {
//            if (!bullet.isBulletActive()) continue;
//
//            for (auto& otherPlayer : m_players) {
//                if (&player != &otherPlayer && bullet.checkCollision(otherPlayer.getPosition().first, otherPlayer.getPosition().second)) {
//                    otherPlayer.loseLife();
//                    bullet.deactivate();
//                    player.addReward(100);
//                    std::cout << otherPlayer.getName() << " was hit by a bullet!\n";
//                }
//            }
//
//            Tile& tile = m_gameMap.getTile(static_cast<int>(bullet.getPosition().first), static_cast<int>(bullet.getPosition().second));
//            if (tile.getType() == TileType::DESTRUCTIBLE_WALL) {
//                tile.destroy();
//                bullet.deactivate();
//                player.addReward(50);
//                std::cout << "A destructible wall was destroyed by a bullet!\n";
//            }
//
//            for (auto& otherBullet : player.getWeapon().getBullets()) {
//                if (&bullet != &otherBullet && bullet.checkCollision(static_cast<int>(otherBullet.getPosition().first), static_cast<int>(otherBullet.getPosition().second))) {
//                    bullet.deactivate();
//                    otherBullet.deactivate();
//                    std::cout << "Two bullets canceled each other out!\n";
//                }
//            }
//        }
//    }
//}
//
//void GameManager::gameLoop() {
//    // while (m_isRunning) {
//    //     detectCollisions();
//    //     system("cls");
//    //     m_gameMap.printMap();
//    //     for (const auto& player : m_players) {
//    //         std::cout << player.getName() << " is at (" << player.getPosition().first << ", " << player.getPosition().second
//    //             << ") with " << player.getLives() << " lives remaining.\n";
//    //     }
//    //     if (_kbhit()) {
//    //         char key = _getch();
//    //         if (key == 'q') {
//    //             m_isRunning = false;
//    //             break;
//    //         }
//    //         if (key == 'w' || key == 'a' || key == 's' || key == 'd') {
//    //             m_players[0].movePlayer(m_players[0], key, m_gameMap.getWidth(), m_gameMap.getHeight(), m_gameMap);
//    //         }
//    //         if (key == 'i' || key == 'j' || key == 'k' || key == 'l') {
//    //             char convertedKey;
//    //             switch (key) {
//    //             case 'i': convertedKey = 'w'; break;
//    //             case 'k': convertedKey = 's'; break;
//    //             case 'j': convertedKey = 'a'; break;
//    //             case 'l': convertedKey = 'd'; break;
//    //             }
//    //             m_players[1].movePlayer(m_players[1], convertedKey, m_gameMap.getWidth(), m_gameMap.getHeight(), m_gameMap);
//    //         }
//    //         if (key == ' ') {
//    //             m_players[0].shoot(Direction::UP);
//    //         }
//    //         else if (key == '\r') {
//    //             m_players[1].shoot(Direction::UP);
//    //         }
//    //     }
//    //     Sleep(100);
//    // }
//}
//
//void GameManager::endGame() {
//    std::cout << "The game has ended!\n";
//    for (const auto& player : m_players) {
//        std::cout << player.getName() << " has a final score of " << player.getScore() << " points!\n";
//    }
//}
//
//std::vector<Player>& GameManager::getPlayers() {
//    return m_players;
//}
//
//void GameManager::generatePowerUps(int count) {
//    for (int i = 0; i < count; ++i) {
//        PowerUp powerUp = PowerUp::generateRandom(
//            m_gameMap.getWidth(), m_gameMap.getHeight(), m_gameMap.getGrid()
//        );
//        m_powerUps.push_back(powerUp);
//        m_gameMap.getTile(powerUp.getX(), powerUp.getY()).setType(TileType::POWERUP);
//    }
//}
//
//
//void GameManager::checkPlayerPowerUpCollision() {
//    for (auto& player : m_players) {
//        for (auto it = m_powerUps.begin(); it != m_powerUps.end();) {
//            if (player.getX() == it->getX() && player.getY() == it->getY()) {
//                switch (it->getType()) {
//                case PowerUp::EXTRA_HP:
//                    player.addHP(1);
//                    break;
//                case PowerUp::SHIELD:
//                    player.activateShield(5);
//                    break;
//                case PowerUp::SPEED_BOOST:
//                    player.increaseSpeed(5);
//                    break;
//                }
//                it = m_powerUps.erase(it);
//            }
//            else {
//                ++it;
//            }
//        }
//    }
//}
//
//void GameManager::renderMap() const {
//    const auto& grid = m_gameMap.getGrid(); // Obține grila hărții
//    for (int y = 0; y < grid.size(); ++y) {
//        for (int x = 0; x < grid[y].size(); ++x) {
//            TileType type = grid[y][x].getType(); // Obține tipul tile-ului curent
//            switch (type) {
//            case TileType::EMPTY:
//                std::cout << '.'; // Reprezentare vizuală pentru spațiu liber
//                break;
//            case TileType::WALL:
//                std::cout << '#'; // Zid indestructibil
//                break;
//            case TileType::DESTRUCTIBLE_WALL:
//                std::cout << '*'; // Zid destructibil
//                break;
//            case TileType::BOMB:
//                std::cout << 'B'; // Bombă (dacă este relevant)
//                break;
//            default:
//                std::cout << '?'; // Necunoscut
//            }
//        }
//        std::cout << std::endl;
//    }
//}
//
