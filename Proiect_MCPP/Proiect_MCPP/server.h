#pragma once

#include <vector>
#include <string>
#include <queue>
#include <mutex>
#include <unordered_map>

// Struct for storing game sessions
struct GameSession {
    int gameId;
    std::vector<std::string> players;
    int maxPlayers;
    std::string serializedPlayers;

    void serialize();
    void deserialize();
};

// Struct for storing scores
struct Score {
    int id;
    std::string player_name;
    int score;
};

// Function declarations
void initServer();
void startServer();
void stopServer();
void startServerWithMultigaming();
