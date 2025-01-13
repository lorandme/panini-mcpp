#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <vector>
#include <mutex>

class Database {
private:
    sqlite3* db;
    std::mutex dbMutex;

    bool executeQuery(const std::string& query);
    bool executeQueryWithResults(const std::string& query, std::vector<std::vector<std::string>>& results);
    bool createUsersTable();

public:
    Database();
    ~Database();

    bool open(const std::string& dbPath);
    void close();

    bool addUser(const std::string& username, const std::string& password);
    bool authenticateUser(const std::string& username, const std::string& password);
    bool userExists(const std::string& username);
};

#endif // DATABASE_H
