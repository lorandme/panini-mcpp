

#include "Server.h"
#include <iostream>
#include <crow.h>
#include <sqlite3.h>
#include "database.h"

Server::Server() : db(nullptr) {
    // Constructorul clasei Server
}

void Server::init() {
    // Inițializare server: deschiderea bazei de date și configurarea rutelor
    if (!openDatabase()) {
        std::cerr << "Eroare la deschiderea bazei de date!" << std::endl;
        return;
    }

    setupRoutes();
}


void Server::run() {
    // Lansează serverul Crow
    std::cout << "Serverul este acum activ!" << std::endl;
    app.port(8080).run();  // Ascultă pe portul 8080
}

bool Server::openDatabase() {
    // Deschide conexiunea la baza de date SQLite
    const char* dbPath = "data.db";  // Calea către fișierul bazei de date
    int rc = sqlite3_open(dbPath, &db);

    if (rc) {
        std::cerr << "Eroare la deschiderea bazei de date: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    std::cout << "Baza de date a fost deschisă cu succes!" << std::endl;
    return true;
}

void Server::closeDatabase() {
    // Închide baza de date SQLite
    if (db) {
        sqlite3_close(db);
        std::cout << "Baza de date a fost închisă!" << std::endl;
    }
}

void Server::setupRoutes() {
    // Configurăm rutele serverului

    // Ruta pentru login
    app.route_dynamic("/login")
        .methods("POST"_method)([this](const crow::request& req) {
        // Obținem username și password din cererea POST
        auto json_data = crow::json::load(req.body);
        if (!json_data) {
            return crow::response(400, "JSON invalid.");
        }

        std::string username = json_data["username"].s();
        std::string password = json_data["password"].s();

        if (authenticate(username, password)) {
            return crow::response(200, "Autentificare reușită!");
        }
        else {
            return crow::response(401, "Autentificare eșuată!");
        }
            });

    CROW_ROUTE(app, "/login")([]() {
        return "<html>"
            "<head><title>Login</title></head>"
            "<body>"
            "<h1>ASTA ESTE PAGINA DE LOGIN</h1>"
            "<form action=\"/submit_login\" method=\"post\">"
            "  <label for=\"username\">Username:</label><br>"
            "  <input type=\"text\" id=\"username\" name=\"username\"><br><br>"
            "  <label for=\"password\">Password:</label><br>"
            "  <input type=\"password\" id=\"password\" name=\"password\"><br><br>"
            "  <input type=\"submit\" value=\"Login\">"
            "</form>"
            "</body>"
            "</html>";
        });

    // Ruta pentru procesarea login-ului
    CROW_ROUTE(app, "/submit_login").methods("POST"_method)([this](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body) {
            return crow::response(400, "Invalid JSON format.");
        }

        std::string username = body["username"].s();
        std::string password = body["password"].s();

        // Salvează sau autentifică utilizatorul
        if (authenticate(username, password)) {
            return crow::response(200, "Login successful!");
        }
        else {
            return crow::response(401, "Invalid username or password!");
        }
        });

    app.route_dynamic("/register")
        .methods("POST"_method)([this](const crow::request& req) {
        // Citim username și parola ca parametri din formular
        std::string username = req.url_params.get("username");
        std::string password = req.url_params.get("password");

        if (username.empty() || password.empty()) {
            return crow::response(400, "Username sau parola sunt goale.");
        }

        // Înregistrăm utilizatorul în baza de date
        if (Database.addUser(username, password)) {
            return crow::response(201, "Utilizator înregistrat cu succes.");
        }
        else {
            return crow::response(500, "Eroare la înregistrarea utilizatorului.");
        }
            });
}

bool Server::authenticate(const std::string& username, const std::string& password) {
    // Autentificare utilizator - Verificăm dacă datele de autentificare sunt corecte

    std::lock_guard<std::mutex> lock(dbMutex);  // Protejăm accesul la baza de date

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
        // Dacă există un rând în baza de date care corespunde, utilizatorul este autentificat
        sqlite3_finalize(stmt);
        return true;
    }
    else {
        sqlite3_finalize(stmt);
        return false;  // Dacă nu există niciun rând corespunzător, autentificarea a eșuat
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

    // Adăugăm utilizatorul în baza de date
    if (db.addUser(username, password)) {
        return true;
    }
    else {
        return false;
    }
}
