#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <mutex>
#include <sqlite3.h>

class Database {
public:
    Database();
    ~Database();

    bool open(const std::string& dbPath);
    void close();

    bool userExists(const std::string& username);
    bool authenticateUser(const std::string& username, const std::string& password);

    bool addUser(const std::string& username, const std::string& password);

    void testDatabaseFunctionality();
    void printAllUsers();



private:
    bool createUsersTable();
    bool executeQuery(const std::string& query);
    bool executeQueryWithResults(const std::string& query, std::vector<std::vector<std::string>>& results);

    sqlite3* db;
    std::mutex dbMutex;
};

#endif
