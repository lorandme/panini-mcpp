

#include "Server.h"
#include <iostream>
#include <crow.h>
#include <sqlite3.h>
#include "database.h"
#include "Bullet.h"
#include "Bomb.h"

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
            return crow::response(201, "Utilizator înregistrat cu succes");
        }
        else {
            return crow::response(500, "Eroare la înregistrarea utilizatorului");
        }
            });

    CROW_ROUTE(app, "/bullets/info")
        .methods("GET"_method)([this](const crow::request& req) {
        // Creează un răspuns JSON
        crow::json::wvalue response;

        // Creează o listă de bule
        auto bulletsList = crow::json::wvalue::list();

        // Exemplu de adăugare a informațiilor despre bulă
        crow::json::wvalue bulletInfo;
        bulletInfo["x"] = 10.0;
        bulletInfo["y"] = 20.0;
        bulletInfo["direction"] = 1; // DOWN
        bulletInfo["active"] = true;

        // Adaugă informațiile despre bulă în lista de bule
        bulletsList.push_back(std::move(bulletInfo));

        // Setează lista de bule în răspuns
        response["bullets"] = std::move(bulletsList);

        return crow::response(response);
            });

    CROW_ROUTE(app, "/bullets/create")
        .methods("POST"_method)([this](const crow::request& req) {
        auto json_data = crow::json::load(req.body);
        if (!json_data) {
            return crow::response(400, "Invalid JSON");
        }

        // Extract bullet parameters
        double startX = json_data["startX"].d();
        double startY = json_data["startY"].d();
        int directionInt = json_data["direction"].i();
        int ownerId = json_data["ownerId"].i();

        // Convert int to Direction enum
        Direction direction;
        switch (directionInt) {
        case 0: direction = Direction::UP; break;
        case 1: direction = Direction::DOWN; break;
        case 2: direction = Direction::LEFT; break;
        case 3: direction = Direction::RIGHT; break;
        default:
            return crow::response(400, "Invalid direction");
        }

        // Create bullet
        Bullet newBullet(startX, startY, direction, ownerId);

        // Răspuns JSON
        crow::json::wvalue response;
        response["message"] = "Bullet created successfully";
        response["x"] = startX;
        response["y"] = startY;

        return crow::response(201, response);
            });

    CROW_ROUTE(app, "/create_bomb")
        .methods("POST"_method)([this](const crow::request& req) {
        auto json_data = crow::json::load(req.body);
        if (!json_data || !json_data.has("x") || !json_data.has("y") || !json_data.has("owner")) {
            return crow::response(400, "JSON invalid.");
        }

        int x = json_data["x"].i();
        int y = json_data["y"].i();
        int owner = json_data["owner"].i();

        Bomb newBomb(x, y, owner);
        bombs.push_back(newBomb); // Use the bombs vector

        return crow::response(201, "Bomb created successfully.");
            });

    // Update bomb route
    CROW_ROUTE(app, "/update_bomb")
        .methods("POST"_method)([this](const crow::request& req) {
        auto json_data = crow::json::load(req.body);
        if (!json_data || !json_data.has("index") || !json_data.has("deltaTime")) {
            return crow::response(400, "JSON invalid.");
        }

        int index = json_data["index"].i();
        float deltaTime = json_data["deltaTime"].d(); // Use d() for double

        if (index < 0 || index >= bombs.size()) {
            return crow::response(404, "Bomb not found.");
        }

        bombs[index].update(deltaTime);

        return crow::response(200, "Bomb updated successfully.");
            });

    // Bombs info route
    CROW_ROUTE(app, "/bombs/info")
        .methods("GET"_method)([this](const crow::request& req) {
        // Create a JSON response
        crow::json::wvalue response;

        // Create a list of bombs
        auto bombsList = crow::json::wvalue::list();

        for (const auto& bomb : bombs) {
            crow::json::wvalue bombInfo;
            bombInfo["x"] = bomb.getX();
            bombInfo["y"] = bomb.getY();
            bombInfo["exploded"] = bomb.isExploded();
            bombInfo["timer"] = bomb.getTimer();
            bombInfo["damageDone"] = bomb.hasDamageDone();

            bombsList.push_back(std::move(bombInfo));
        }

        response["bombs"] = std::move(bombsList);

        return crow::response(200, response.dump());
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
