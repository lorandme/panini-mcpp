#include <sqlite3.h>
#include <iostream>
#include <stdexcept>

void initializeDatabase(const std::string& db_name) {
    sqlite3* db;
    char* err_msg = nullptr;

    // Deschide baza de date (se creează dacă nu există)
    if (sqlite3_open(db_name.c_str(), &db) != SQLITE_OK) {
        throw std::runtime_error("Cannot open database: " + std::string(sqlite3_errmsg(db)));
    }

    // Creează tabelul `players`
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS players (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password_hash TEXT NOT NULL,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP
        );
    )";

    if (sqlite3_exec(db, sql, 0, 0, &err_msg) != SQLITE_OK) {
        std::string error_message = err_msg;
        sqlite3_free(err_msg);
        sqlite3_close(db);
        throw std::runtime_error("SQL error: " + error_message);
    }

    std::cout << "Database initialized and table `players` created successfully.\n";
    sqlite3_close(db);
}

int main() {
    try {
        initializeDatabase("battle_city.db");
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
