//#pragma once
//
//#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <string>
//#include <nlohmann/json.hpp>
//
//class Client {
//private:
//    SOCKET m_socket;
//    std::string m_serverIP;
//    int m_serverPort;
//
//public:
//    Client(const std::string& serverIP, int serverPort);
//
//    ~Client();
//
//    void init();
//
//    // Functie pentru conversia unui sir wide char in UTF-8
//    std::string wstringToUtf8(const std::wstring& wstr);
//
//    // Trimiterea unui mesaj catre server
//    void sendMessage(const nlohmann::json& request);
//
//    // Primirea unui raspuns de la server
//    nlohmann::json receiveMessage();
//};
#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
public:
    // Constructor
    Client(const std::string& serverUrl);

    // Funcție pentru înregistrare utilizator
    bool registerUser(const std::string& username, const std::string& password);

    // Funcție pentru autentificare utilizator
    bool login(const std::string& username, const std::string& password);

private:
    std::string serverUrl;  // URL-ul serverului la care se face cererea
};

#endif // CLIENT_H


