#include "LoginPage.h"
#include <crow.h>
#include <sqlite3.h>
#include <iostream>

LoginPage::LoginPage(sqlite3* db) : db(db) {}

void LoginPage::setupRoutes(crow::SimpleApp& app) {
    // Ruta pentru autentificare
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
}

bool LoginPage::authenticate(const std::string& username, const std::string& password) {
    // Autentificare utilizator - Verificăm dacă datele de autentificare sunt corecte
    std::lock_guard<std::mutex> lock(dbMutex);  // Protejăm accesul la baza de date

    std::string sql = "SELECT * FROM users WHERE username = ? AND password = ?";
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
