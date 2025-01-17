
#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
public:
    Client(const std::string& serverUrl);
    bool registerUser(const std::string& username, const std::string& password);
    bool login(const std::string& username, const std::string& password);

private:
    std::string serverUrl; 
};

#endif 


