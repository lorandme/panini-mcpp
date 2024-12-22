#include <iostream>
#include "sqlite3.h"
#include "database.h"

void initializeDatabase() {
    sqlite3* db;
    char* errMessage = 0;

    // Deschide sau creează baza de date
    const char* db_path = "C:/Users/matei/Documents/Proiect_MC/Proiect_MCPP/Proiect_MCPP/battle_city.db";
    int rc = sqlite3_open(db_path, &db);
    if (rc) {
        std::cerr << "Nu s-a putut deschide baza de date: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // Creează tabela Users dacă nu există deja
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS Users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL
        );
    )";

    rc = sqlite3_exec(db, sql, 0, 0, &errMessage);
    if (rc != SQLITE_OK) {
        std::cerr << "Eroare la crearea tabelei Users: " << errMessage << std::endl;
        sqlite3_free(errMessage);
    }
    else {
        std::cout << "Tabela 'Users' a fost creata sau exista deja.\n";
    }

    sqlite3_close(db);
}
