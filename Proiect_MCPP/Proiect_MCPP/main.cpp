
#include <iostream>
#include "server.h"
#include "database.h"
#include "../PlayerDLL/PlayerLogger.h"; 

int main() {
    try {
        PlayerLogger logger("../log.txt"); 
        logger.LogPlayerMove("Player1", 10, 20);  

        Server server;  
        server.init(); 
        server.run();   

        std::cout << "Serverul rulează pe portul 8080..." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "A apărut o eroare: " << e.what() << std::endl;
        return 1;  
    }


    Database open();
    return 0;
}

//PROBA PENTRU A TESTA CA DATELE SE STOCHEAZA CORECT IN BAZA DE DATE
//
//#include "database.h"
//#include <iostream>
//
//int main() {
//    Database db;
//
//    if (!db.open("data.db")) {
//        std::cerr << "Eroare la deschiderea bazei de date!" << std::endl;
//        return 1;
//    }
//
//    // Adăugăm un utilizator pentru test
//    db.addUser("testuser", "testpass");
//
//    // Verificăm dacă utilizatorul a fost adăugat
//    if (db.userExists("testuser")) {
//        std::cout << "Utilizatorul `testuser` există în baza de date!\n";
//    }
//
//    // Afișăm toți utilizatorii din tabel
//    db.printAllUsers();
//
//    db.close();
//    return 0;
//}
//
