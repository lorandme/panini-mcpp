
#include "Client.h"
#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

Client::Client(const std::string& serverUrl) : serverUrl(serverUrl) {}

Client::Client() {
 
}

cpr::Response Client::registerUser(const std::string& username, const std::string& password) {
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
        return cpr::Post(
            cpr::Url{ "http://localhost:8080/register" },
            cpr::Body{ R"({"username":")" + username + R"(","password":")" + password + R"("})" },
            cpr::Header{ {"Content-Type", "application/json"} }
        );
    }
    else {
        std::cerr << "Eroare la înregistrare: " << response.text << std::endl;
        return cpr::Post(cpr::Url{ "http://localhost:invalid" });
    }

}   

bool Client::login(const std::string& username, const std::string& password) {
    nlohmann::json json_data;
    json_data["username"] = username;
    json_data["password"] = password;

    cpr::Response response = cpr::Post(
        cpr::Url{ "http://localhost:8080/login" },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ json_data.dump() }
    );

    if (response.status_code == 200) {
        std::cout << "Autentificare reușită!" << std::endl;
        return true; 
    }
    else if (response.status_code == 401) {
        std::cerr << "Autentificare eșuată: Username sau parolă incorecte!" << std::endl;
        return false; 
    }
    else {
        std::cerr << "Eroare la autentificare: " << response.text << std::endl;
        return false;
    }
}

