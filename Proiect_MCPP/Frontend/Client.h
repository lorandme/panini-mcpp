#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <cpr/cpr.h>

class Client {
public:
    Client(const std::string& serverUrl);
    Client();
    cpr::Response registerUser(const std::string& username, const std::string& password);
    bool login(const std::string& username, const std::string& password); 
private:
    std::string serverUrl;
};
#endif