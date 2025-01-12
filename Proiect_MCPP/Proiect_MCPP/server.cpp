//#pragma once
//#include <winsock2.h>
//#include <ws2tcpip.h>
//
//#include <iostream>
//#include <thread>
//#include <vector>
//#include <mutex>
//#include <unordered_map>
//#include <string>
//#include <cstring>  
//
//#include "Team.h"
//#include "Player.h"
//#include "Tile.h"
//#include "Weapon.h"
//#include <nlohmann/json.hpp>  
//using json = nlohmann::json;
//
//class Server {
//private:
//    int m_serverSocket;
//    int m_port;
//    std::mutex m_mutex;
//    std::unordered_map<int, std::thread> m_clientThreads;
//    std::vector<Team> m_teams;
//
//public:
//    Server(int port) : m_port(port), m_serverSocket(-1) {}
//
//    ~Server() {
//#ifdef _WIN32
//        WSACleanup();
//#endif
//        // Închide toate conexiunile clienților și oprește serverul
//        for (auto& [_, clientThread] : m_clientThreads) {
//            if (clientThread.joinable()) {
//                clientThread.join();
//            }
//        }
//        if (m_serverSocket != -1) {
//            closesocket(m_serverSocket);
//        }
//    }
//
//    void init() {
//        // Creare socket
//#ifdef _WIN32
//        WSADATA wsaData;
//        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
//            throw std::runtime_error("Eroare la initializarea WinSock.");
//        }
//#endif
//
//        m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
//        if (m_serverSocket == -1) {
//            throw std::runtime_error("Eroare la crearea socket-ului serverului.");
//        }
//
//        sockaddr_in serverAddr{};
//        serverAddr.sin_family = AF_INET;
//        serverAddr.sin_addr.s_addr = INADDR_ANY;
//        serverAddr.sin_port = htons(m_port);
//
//        // Asociere socket cu port
//        if (bind(m_serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
//            throw std::runtime_error("Eroare la asocierea socket-ului serverului.");
//        }
//
//        // Ascultare conexiuni
//        if (listen(m_serverSocket, 5) < 0) {
//            throw std::runtime_error("Eroare la ascultarea conexiunilor.");
//        }
//
//        std::cout << "Serverul ruleaza pe portul " << m_port << std::endl;
//    }
//
//    void start() {
//        while (true) {
//            sockaddr_in clientAddr{};
//            socklen_t clientLen = sizeof(clientAddr);
//            int clientSocket = accept(m_serverSocket, (struct sockaddr*)&clientAddr, &clientLen);
//
//            if (clientSocket >= 0) {
//                std::lock_guard<std::mutex> lock(m_mutex);
//                m_clientThreads[clientSocket] = std::thread(&Server::handleClient, this, clientSocket);
//                std::cout << "Un nou client s-a conectat." << std::endl;
//            }
//        }
//    }
//
//    void stopServer() {
//        // Nouă metodă pentru oprirea serverului și a tuturor conexiunilor active
//        std::lock_guard<std::mutex> lock(m_mutex);
//        for (auto& [clientSocket, clientThread] : m_clientThreads) {
//            if (clientThread.joinable()) {
//                clientThread.join();
//                closesocket(clientSocket); // Închide socket-ul clientului
//            }
//        }
//        if (m_serverSocket != -1) {
//            closesocket(m_serverSocket);  // Închide socket-ul serverului
//            m_serverSocket = -1; // Mark server socket as closed
//        }
//        std::cout << "Serverul a fost oprit." << std::endl;
//    }
//
//private:
//    void handleClient(int clientSocket) {
//        try {
//            char buffer[1024];
//            while (true) {
//                memset(buffer, 0, sizeof(buffer));
//                int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
//
//                if (bytesReceived <= 0) {
//                    std::cout << "Clientul s-a deconectat." << std::endl;
//                    closesocket(clientSocket);
//                    break;
//                }
//
//                std::string message(buffer);
//
//                // Protejează parsing-ul JSON cu try-catch
//                json request;
//                try {
//                    request = json::parse(message);  // Încearcă să parsezi mesajul
//                }
//                catch (const std::exception& e) {
//                    std::cerr << "Eroare la parsing-ul JSON: " << e.what() << std::endl;
//                    json response;
//                    response["status"] = "error";
//                    response["message"] = "Mesajul trimis nu este un JSON valid.";
//                    std::string responseStr = response.dump();
//                    send(clientSocket, responseStr.c_str(), responseStr.size(), 0);
//                    continue;  // Mergi mai departe fără a continua procesarea pentru acest mesaj
//                }
//
//                json response = processRequest(request);
//
//                std::string responseStr = response.dump();
//                send(clientSocket, responseStr.c_str(), responseStr.size(), 0);
//            }
//        }
//        catch (const std::exception& e) {
//            std::cerr << "Eroare la gestionarea clientului: " << e.what() << std::endl;
//            closesocket(clientSocket);
//        }
//    }
//
//    json processRequest(const json& request) {
//        std::string command = request["message"];  // Citim mesajul trimis de client
//        json response;
//
//        if (command == "Salut server") {
//            // Dacă mesajul este "Salut server", răspundem corespunzător
//            response["status"] = "ok";
//            response["message"] = "Salut, client!";
//        }
//        else {
//            response["status"] = "error";
//            response["message"] = "Comandă necunoscută.";
//        }
//
//        return response;
//    }
//
//    Team* findOrCreateTeam(const std::string& teamName) {
//        // Dacă echipa există deja, returnează-o, altfel o creează
//        for (auto& team : m_teams) {
//            if (team.getName() == teamName) {
//                return &team;
//            }
//        }
//
//        m_teams.emplace_back(teamName);  // Creează echipa dacă nu există
//        return &m_teams.back();  // Returnează ultima echipă creată
//    }
//
//    Team* findTeam(const std::string& teamName) {
//        // Căutăm echipa după nume
//        for (auto& team : m_teams) {
//            if (team.getName() == teamName) {
//                return &team;
//            }
//        }
//        return nullptr; // Dacă nu găsește echipa, returnează nullptr
//    }
//};

#include "Server.h"
#include <iostream>
#include <crow.h>
#include <sqlite3.h>

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

    // Poți adăuga și alte rute pentru operațiuni suplimentare.
}

bool Server::authenticate(const std::string& username, const std::string& password) {
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

