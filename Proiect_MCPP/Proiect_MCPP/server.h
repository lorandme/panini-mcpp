#pragma once
#include <crow.h>
#include <sqlite3.h>
#include <mutex>
#include "Bomb.h"
#include <vector>
#include <string>
#include "Map.h"  
#include "Database.h"
#include "PowerUp.h"
#include "Tile.h"
#include "Player.h"




class Server {
private:
    crow::SimpleApp app;
    sqlite3* db;  
    std::mutex dbMutex;
    std::vector<Bomb> bombs;

public:
    Server();
    void init();
    void run();

private:
    void setupRoutes();
    bool authenticate(const std::string& username, const std::string& password);
    bool openDatabase();
    void closeDatabase();
    bool registerUser(const std::string& username, const std::string& password);
};