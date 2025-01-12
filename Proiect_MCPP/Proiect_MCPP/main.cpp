
#include <iostream>
#include "server.h"

int main() {
    try {
        Server server;  // Creează obiectul server
        server.init();  // Inițializează serverul (configurare baze de date, rute, etc.)
        server.run();   // Lansează serverul să asculte pentru cereri

        std::cout << "Serverul rulează pe portul 8080..." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "A apărut o eroare: " << e.what() << std::endl;
        return 1;  // Returnează un cod de eroare
    }

    return 0;
}

