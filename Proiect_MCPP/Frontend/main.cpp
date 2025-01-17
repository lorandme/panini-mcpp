#include "Client.h"
#include <iostream>
#include <string>

int main() {
    Client client("http://localhost:8080");

    std::string username, password;
    std::cout << "Introduceți username: ";
    std::cin >> username;
    std::cout << "Introduceți parola: ";
    std::cin >> password;

    if (client.registerUser(username, password)) {
        std::cout << "Înregistrare reușită!" << std::endl;
    }
    else {
        std::cout << "Înregistrare eșuată!" << std::endl;
    }

    return 0;
}

//PROBA PENTRU BAZA DE DATE