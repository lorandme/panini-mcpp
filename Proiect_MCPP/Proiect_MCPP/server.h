#pragma once

#include <vector>
#include <string>
#include <queue>
#include <mutex>
#include <unordered_map>

struct GameSession {
    int gameId;                       
    std::vector<std::string> players;  
    int maxPlayers;                   
    std::string serializedPlayers;   

    void serialize();
    void deserialize();
};

struct Score {
    int id;              
    std::string playerName; 
    int score;           
};

struct User {
    int id;
    std::string username;
    std::string email;      
    std::string password;   
};


void initServer();
void startServer();
void stopServer();
void startServerWithMultigaming();
