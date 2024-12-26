#include <iostream>
#include <sqlite3.h>
#include "database.h"
#include <fstream>
#include <direct.h>
#include <Windows.h>


//Un path pentru database sa functioneze pentru toata lumea
std::string getDatabasePath() {
   
    char buffer[MAX_PATH];
    _getcwd(buffer, MAX_PATH); 
    std::string dbPath = std::string(buffer) + "\\battle_city.db";  
    return dbPath;
}

void initializeDatabase() {
    sqlite3* db;
    char* errMessage = 0;

    
    std::string db_path = getDatabasePath();

    int rc = sqlite3_open(db_path.c_str(), &db);
    if (rc) {
        std::cerr << "Nu s-a putut deschide baza de date: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

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
