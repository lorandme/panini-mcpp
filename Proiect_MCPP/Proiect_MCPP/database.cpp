#include "Database.h"
#include <iostream>

Database::Database() : db(nullptr) {}

Database::~Database() {
    close();
}

bool Database::createUsersTable() {
    std::string createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL
        );
    )";
    return executeQuery(createTableQuery);
}

bool Database::open(const std::string& dbPath) {
    std::lock_guard<std::mutex> lock(dbMutex);
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Nu s-a putut deschide baza de date: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Creează tabela users dacă nu există
    if (!createUsersTable()) {
        std::cerr << "Eroare la crearea tabelei users!" << std::endl;
        return false;
    }

    return true;
}

void Database::close() {
    std::lock_guard<std::mutex> lock(dbMutex);
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool Database::executeQuery(const std::string& query) {
    std::lock_guard<std::mutex> lock(dbMutex);
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Eroare la executarea interogării: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

bool Database::executeQueryWithResults(const std::string& query, std::vector<std::vector<std::string>>& results) {
    std::lock_guard<std::mutex> lock(dbMutex);
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Eroare la pregătirea interogării: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    rc = sqlite3_step(stmt);
    while (rc == SQLITE_ROW) {
        std::vector<std::string> row;
        for (int col = 0; col < sqlite3_column_count(stmt); ++col) {
            row.push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, col)));
        }
        results.push_back(row);
        rc = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}

bool Database::userExists(const std::string& username) {
    std::lock_guard<std::mutex> lock(dbMutex);
    std::string query = "SELECT COUNT(*) FROM users WHERE username = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Eroare la pregătirea interogării: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);

    bool exists = false;
    if (rc == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0) > 0;
    }

    sqlite3_finalize(stmt);
    return exists;
}

bool Database::authenticateUser(const std::string& username, const std::string& password) {
    std::lock_guard<std::mutex> lock(dbMutex);
    std::string query = "SELECT COUNT(*) FROM users WHERE username = ? AND password = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Eroare la pregătirea interogării: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);

    bool authenticated = false;
    if (rc == SQLITE_ROW) {
        authenticated = sqlite3_column_int(stmt, 0) > 0;
    }

    sqlite3_finalize(stmt);
    return authenticated;
}
