#ifndef SERVER_H
#define SERVER_H

#include <crow.h>
#include <sqlite3.h>
#include <mutex>

class Server {
public:
    Server(); // Constructor
    void init(); // Inițializare server și conexiune la DB
    void run(); // Lansează serverul

private:
    bool openDatabase(); // Deschide baza de date
    void closeDatabase(); // Închide baza de date
    void setupRoutes(); // Configurează rutele
    bool authenticate(const std::string& username, const std::string& password); // Autentifică utilizatorii
    bool registerUser(const std::string& username, const std::string& password); // Înregistrează utilizatori noi

    sqlite3* db; // Conexiune la baza de date SQLite
    crow::SimpleApp app; // Serverul Crow
    std::mutex dbMutex; // Mutex pentru a proteja accesul la baza de date
};

#endif
