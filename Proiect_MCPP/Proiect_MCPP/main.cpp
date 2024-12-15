#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "Server.cpp"
#include "Client.cpp"
#include <iostream>

void startServer() {
    // Creează și inițializează serverul pe portul 12345
    Server server(12345);
    server.init();
    server.start();  // Pornește serverul pentru a asculta clienții
}

void startClient() {
    // Crează clientul și se conectează la serverul de pe 127.0.0.1 pe portul 12345
    Client client("127.0.0.1", 12345);
    client.init();

    // Exemplu de cerere JSON pentru a adăuga un jucător într-o echipă
    json request;
    request["command"] = "join_team";
    request["team_name"] = "Echipa1";
    request["player_name"] = "Jucator1";

    // Trimite cererea către server
    client.sendMessage(request);

    // Așteaptă un răspuns de la server
    json response = client.receiveMessage();
    std::cout << "Raspunsul serverului  " << response.dump() << std::endl;
}

int main() {
    // Inițializare GameManager
    GameManager gameManager;

    // Inițializare joc
    gameManager.initializeGame();

    // Start joc
    std::cout << "Jocul a inceput! \n";
    gameManager.startGame();

    // TESTARE SFML
    /*sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }*/

    std::cout << "Testare recompense:\n";
    auto& players = gameManager.getPlayers(); // Obține referința la jucători
    players[0].addReward(50); // Exemplu de recompensă
    std::cout << players[0].getName() << " are acum " << players[0].getScore() << " puncte.\n";

    // Inițializează serverul (opțional, dacă ai nevoie să sincronizezi schema bazei de date)
    //initServer();

    // Pornește serverul cu funcționalitatea de multigaming
    //startServerWithMultigaming();


    // Pornește serverul într-un thread separat
    std::thread serverThread(startServer);

    // Așteaptă un moment pentru ca serverul să se inițializeze și să înceapă să asculte
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Pornește clientul care va trimite o cerere către server
    startClient();

    // Așteaptă ca serverul să termine procesarea cererii și să finalizeze execuția
    serverThread.join();
    return 0;
}
