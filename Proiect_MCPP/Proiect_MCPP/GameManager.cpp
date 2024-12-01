#include "GameManager.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

// Constructor GameManager
GameManager::GameManager() : gameMap(10, 10), isRunning(false) {}

// Inițializare joc
void GameManager::initializeGame() {
    // Creăm harta de 10x10
    gameMap = Map(10, 10);

    // Adăugăm jucători
    players.emplace_back(Player("Player1", 0, 0)); // Jucător 1 în colțul stânga-sus
    players.emplace_back(Player("Player2", 9, 9)); // Jucător 2 în colțul dreapta-jos

    isRunning = true;
}

// Pornire joc
void GameManager::startGame() {
    gameLoop();
    endGame();
}

// **Metoda detectCollisions (Aici este definită)**
void GameManager::detectCollisions() {
    for (auto& player : players) {
        for (auto& bullet : player.getWeapon().getBullets()) { // Folosim referință non-const
            if (!bullet.isBulletActive()) continue;

            // Coliziunea cu jucători
            for (auto& otherPlayer : players) {
                if (&player != &otherPlayer && bullet.checkCollision(otherPlayer.getPosition().first, otherPlayer.getPosition().second)) {
                    otherPlayer.loseLife();
                    bullet.deactivate();
                    player.addReward(100); // Recompensă pentru eliminarea unui jucător
                    std::cout << otherPlayer.getName() << " a fost lovit de un glonț!\n";
                }
            }

            // Coliziunea cu ziduri destructibile
            Tile& tile = gameMap.getTile(static_cast<int>(bullet.getPosition().first), static_cast<int>(bullet.getPosition().second));
            if (tile.getType() == TileType::DESTRUCTIBLE_WALL) {
                tile.destroy();
                bullet.deactivate();
                player.addReward(50); // Recompensă pentru distrugerea unui zid destructibil
                std::cout << "Un zid destructibil a fost distrus de un glonț!\n";
            }

            // Coliziunea cu alte gloanțe
            for (auto& otherBullet : player.getWeapon().getBullets()) { // Ambele trebuie să fie non-const
                if (&bullet != &otherBullet && bullet.checkCollision(static_cast<int>(otherBullet.getPosition().first), static_cast<int>(otherBullet.getPosition().second))) {
                    bullet.deactivate();
                    otherBullet.deactivate();
                    std::cout << "Două gloanțe s-au anulat reciproc!\n";
                }
            }
        }

    }
}

// Bucla principală de joc
void GameManager::gameLoop() {
    //while (isRunning) {
    //    // Detectează coliziunile
    //    detectCollisions();

    //    // Curățăm ecranul
    //    system("cls");

    //    // Afișăm harta
    //    gameMap.printMap();

    //    // Afișăm pozițiile și starea jucătorilor
    //    for (const auto& player : players) {
    //        std::cout << player.getName() << " este la (" << player.getPosition().first << ", " << player.getPosition().second
    //            << ") cu " << player.getLives() << " vieți rămase.\n";
    //    }

    //    // Capturăm input-ul de la jucători
    //    if (_kbhit()) {
    //        char key = _getch();

    //        // Ieșire din joc
    //        if (key == 'q') {
    //            isRunning = false;
    //            break;
    //        }

    //        // Controlul jucătorului 1 (WASD pentru mișcare)
    //        if (key == 'w' || key == 'a' || key == 's' || key == 'd') {
    //            players[0].movePlayer(players[0], key, gameMap.getWidth(), gameMap.getHeight(), gameMap);
    //        }

    //        // Controlul jucătorului 2 (IJKL pentru mișcare)
    //        if (key == 'i' || key == 'j' || key == 'k' || key == 'l') {
    //            char convertedKey;
    //            switch (key) {
    //            case 'i': convertedKey = 'w'; break;
    //            case 'k': convertedKey = 's'; break;
    //            case 'j': convertedKey = 'a'; break;
    //            case 'l': convertedKey = 'd'; break;
    //            }
    //            players[1].movePlayer(players[1], convertedKey, gameMap.getWidth(), gameMap.getHeight(), gameMap);
    //        }

    //        // Trage un glonț (tasta SPACE pentru jucător 1, ENTER pentru jucător 2)
    //        if (key == ' ') {
    //            players[0].shoot(Direction::UP);
    //        }
    //        else if (key == '\r') {
    //            players[1].shoot(Direction::UP);
    //        }
    //    }

    //    // Pauză scurtă pentru a preveni utilizarea excesivă a CPU-ului
    //    Sleep(100);
    //}
}

// Încheiere joc
void GameManager::endGame() {
    std::cout << "Jocul s-a incheiat!\n";

    // Afișăm scorurile finale
    for (const auto& player : players) {
        std::cout << player.getName() << " are un scor final de " << player.getScore() << " puncte!\n";
    }
}

std::vector<Player>& GameManager::getPlayers() {
    return players;
}

