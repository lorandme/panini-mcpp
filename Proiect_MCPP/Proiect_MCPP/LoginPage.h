#pragma once

#include "crow.h"
#include <string>
#include <sqlite3.h>
#include <mutex>

class LoginPage {
private:
    sqlite3* db;  // Pointer la baza de date SQLite
    std::mutex dbMutex;

public:
    LoginPage(sqlite3* db);
    void setupRoutes(crow::SimpleApp& app);

private:
    bool authenticate(const std::string& username, const std::string& password);
};
