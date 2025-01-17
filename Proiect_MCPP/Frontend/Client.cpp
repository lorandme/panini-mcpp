
#include "Client.h"
#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>// Folosim biblioteca CPR pentru cereri HTTP

Client::Client(const std::string& serverUrl) : serverUrl(serverUrl) {}

bool Client::registerUser(const std::string& username, const std::string& password) {
    nlohmann::json json_data;
    json_data["username"] = username;
    json_data["password"] = password;

    cpr::Response response = cpr::Post(
        cpr::Url{ "http://localhost:8080/register" },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ json_data.dump() }
    );

    if (response.status_code == 201) { 
        std::cout << "Înregistrare reușită!" << std::endl;
        return true;
    }
    else {
        std::cerr << "Eroare la înregistrare: " << response.text << std::endl;
        return false;
    }
}   

bool Client::login(const std::string& username, const std::string& password) {
    std::string url = serverUrl + "/login";  
    cpr::Payload payload = { {"username", username}, {"password", password} };

    cpr::Response response = cpr::Post(cpr::Url{ url }, payload);

    if (response.status_code == 200) {
        std::cout << "Autentificare reușită!" << std::endl;
        return true;
    }
    else {
        std::cout << "Autentificare eșuată: " << response.text << std::endl;
        return false;
    }
}
