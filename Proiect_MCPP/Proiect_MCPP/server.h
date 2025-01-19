#pragma once

#include "crow.h"
#include <string>
#include <sqlite3.h>
#include <mutex>
#include "Bomb.h"
#include <vector>



class Server {
private:
    crow::SimpleApp app;
    sqlite3* db;  // Pointer la baza de date SQLite
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