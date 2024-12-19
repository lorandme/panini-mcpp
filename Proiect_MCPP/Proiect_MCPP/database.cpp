#include "Database.h"
#include <iostream>

Database::Database() : db(nullptr) {}

Database::~Database() {
    close();
}


void Database::testDatabaseFunctionality() {
    std::cout << "=== Testarea bazei de date ===" << std::endl;

    std::string testUsername = "testuser";
    std::string testPassword = "testpass";

    if (addUser(testUsername, testPassword)) {
        std::cout << "Utilizatorul '" << testUsername << "' a fost adăugat cu succes." << std::endl;
    }
    else {
        std::cerr << "Eroare la adăugarea utilizatorului de test!" << std::endl;
    }


    if (userExists(testUsername)) {
        std::cout << "Utilizatorul '" << testUsername << "' există în baza de date." << std::endl;
    }
    else {
        std::cerr << "Utilizatorul '" << testUsername << "' NU există în baza de date!" << std::endl;
    }


    std::vector<std::vector<std::string>> results;
    std::string query = "SELECT id, username, password FROM data;";
    if (executeQueryWithResults(query, results)) {
        std::cout << "Utilizatori în baza de date:" << std::endl;
        for (const auto& row : results) {
            std::cout << "ID: " << row[0] << ", Username: " << row[1] << ", Password: " << row[2] << std::endl;
        }
    }
    else {
        std::cerr << "Eroare la obținerea utilizatorilor din baza de date!" << std::endl;
    }

    std::cout << "=== Test finalizat ===" << std::endl;
}

bool Database::createUsersTable() {
    std::string createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS data (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL
        );
    )";
    return executeQuery(createTableQuery);
}

void Database::printAllUsers() {
   
    std::string query = "SELECT id, username, password FROM data;";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Eroare la pregătirea interogării: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::cout << "Conținutul tabelului data:\n";
    std::cout << "ID | Username | Password\n";
    std::cout << "-------------------------\n";

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

        std::cout << id << " | " << (username ? username : "NULL") << " | "
            << (password ? password : "NULL") << "\n";
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "Eroare la iterarea rezultatelor: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}



bool Database::open(const std::string& dbPath) {

    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Nu s-a putut deschide baza de date: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }


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
 
        sqlite3_stmt * stmt;
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
    std::string query = "SELECT COUNT(*) FROM data WHERE username = ?;";
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
        std::string query = "SELECT COUNT(*) FROM data WHERE username = ? AND password = ?;";
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

bool Database::addUser(const std::string& username, const std::string& password) {
    std::string query = "INSERT INTO data (username, password) VALUES (?, ?);";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Eroare la pregătirea interogării: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (rc != SQLITE_DONE) {
        if (rc == SQLITE_CONSTRAINT) {
            std::cerr << "Utilizatorul " << username << " există deja în baza de date." << std::endl;
        }
        else {
            std::cerr << "Eroare la adăugarea utilizatorului: " << sqlite3_errmsg(db) << std::endl;
        }
        return false;
    }
    return true;
}