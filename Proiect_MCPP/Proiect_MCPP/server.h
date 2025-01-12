#pragma once


#include <vector>
#include "crow.h"
#include <string>
#include <queue>
#include <sqlite3.h>
#include <mutex>
#include <unordered_map>


class Server {
private:
    crow::SimpleApp app;
    sqlite3* db;  // Pointer la baza de date SQLite
    std::mutex dbMutex;

public:
    Server();
    void init();
    void run();

private:
    void setupRoutes();
    bool authenticate(const std::string& username, const std::string& password);
    bool openDatabase();
    void closeDatabase();
};