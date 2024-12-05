#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <numeric>

// Funcția pentru inițializarea serverului
void initServer();

// Funcția pentru a începe rularea serverului
void startServer();

// Funcția pentru a închide serverul
void stopServer();

// Funcția pentru a actualiza poziția tancului
void updateTankPosition(int x, int y);

// Funcția pentru a obține scorul de pe server
int getScore();

// Funcția pentru a trimite un răspuns către client
void sendResponse(const std::string& message);

// Funcția pentru a gestiona conexiunile de la clienți
void handleClientConnections();

// Funcția pentru a trata cererile HTTP
void handleHttpRequests();

void startServerWithMultigaming();

struct GameSession {
    int gameId;
    std::vector<std::string> players;
    int maxPlayers;

    // Serializare vector în șir
    std::string serializePlayers() const {
        std::string result;
        for (const auto& player : players) {
            if (!result.empty()) {
                result += ","; // Separator
            }
            result += player;
        }
        return result;
    }

    // Deserializare șir în vector
    void deserializePlayers(const std::string& data) {
        players.clear();
        std::istringstream stream(data);
        std::string player;
        while (std::getline(stream, player, ',')) {
            players.push_back(player);
        }
    }
};