#include "Server.h"
#include <iostream>
#include <crow.h>
#include <sqlite3.h>
#include <regex>
#include "database.h"

Server::Server() : db(nullptr) {
}

void Server::init() {
    if (!openDatabase()) {
        std::cerr << "Eroare la deschiderea bazei de date!" << std::endl;
        return;
    }

    setupRoutes();
}


void Server::run() {
    std::cout << "Serverul este acum activ!" << std::endl;
    app.port(8080).run();  
}

bool Server::openDatabase() {
    const char* dbPath = "data.db";  
    int rc = sqlite3_open(dbPath, &db);

    if (rc) {
        std::cerr << "Eroare la deschiderea bazei de date: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    std::cout << "Baza de date a fost deschisa cu succes" << std::endl;
    return true;
}

void Server::closeDatabase() {
    if (db) {
        sqlite3_close(db);
        std::cout << "Baza de date a fost închisă!" << std::endl;
    }
}

void Server::setupRoutes() {

    app.route_dynamic("/login")
        .methods("POST"_method)([this](const crow::request& req) {
        auto json_data = crow::json::load(req.body);
        if (!json_data) {
            return crow::response(400, "JSON invalid.");
        }

        std::string username = json_data["username"].s();
        std::string password = json_data["password"].s();

        std::regex username_regex("^[a-zA-Z0-9]{3,15}$");

        if (!std::regex_match(username, username_regex)) {
            return crow::response(400, "Invalid username format. Must be 3-15 alphanumeric characters.");
        }

        if (authenticate(username, password)) {
            return crow::response(200, "Autentificare reușită!");
        }
        else {
            return crow::response(401, "Autentificare eșuată!");
        }
            });


    CROW_ROUTE(app, "/submit_login").methods("POST"_method)([this](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body) {
            return crow::response(400, "Invalid JSON format.");
        }

        std::string username = body["username"].s();
        std::string password = body["password"].s();


        if (authenticate(username, password)) {
            return crow::response(200, "Login successful!");
        }
        else {
            return crow::response(401, "Invalid username or password!");
        }
        });

    CROW_ROUTE(app, "/register")
        .methods("POST"_method)([this](const crow::request& req) {
        auto json_data = crow::json::load(req.body);
        if (!json_data) {
            return crow::response(400, "JSON invalid");
        }

        std::string username = json_data["username"].s();
        std::string password = json_data["password"].s();

        if (username.empty() || password.empty()) {
            return crow::response(400, "Username sau parola sunt goale");
        }

        if (registerUser(username, password)) {
            return crow::response(201, "Utilizator inregistrat cu succes");
        }
        else {
            return crow::response(500, "Eroare la inregistrarea utilizatorului");
        }
            });
}

bool Server::authenticate(const std::string& username, const std::string& password) {
 

    std::string sql = "SELECT * FROM data WHERE username = ? AND password = ?";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Eroare la pregătirea interogării: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return true;
    }
    else {
        sqlite3_finalize(stmt);
        return false;
    }
}





bool Server::registerUser(const std::string& username, const std::string& password) {
    Database db;
    if (!db.open("data.db")) {
        std::cerr << "Eroare la deschiderea bazei de date!" << std::endl;
        return false;
    }

    if (db.userExists(username)) {
        std::cerr << "Utilizatorul există deja!" << std::endl;
        return false;
    }

    if (db.addUser(username, password)) {
        return true;
    }
    else {
        return false;
    }
}


void setupRoutes(crow::SimpleApp& app, Database& database) {
    app.route_dynamic("/register").methods("POST"_method)
        ([&database](const crow::request& req) {
        auto json_data = crow::json::load(req.body);
        if (!json_data || !json_data.has("username") || !json_data.has("password")) {
            return crow::response(400, "JSON invalid.");
        }

        std::string username = json_data["username"].s();
        std::string password = json_data["password"].s();

        if (database.userExists(username)) {
            return crow::response(409, "Utilizator deja existent.");
        }

        if (database.addUser(username, password)) {
            return crow::response(201, "Utilizator înregistrat cu succes.");
        }
        else {
            return crow::response(500, "Eroare la inserarea în baza de date.");
        }
            });
}