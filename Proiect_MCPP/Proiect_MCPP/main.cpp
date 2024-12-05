#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "server.h"
#include <iostream>

int main() {
    // Inițializare GameManager
    GameManager gameManager;

    // Inițializare joc
    gameManager.initializeGame();

    // Start joc
    std::cout << "Jocul a inceput! \n";
    gameManager.startGame();

    // TESTARE SFML
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
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
    }

    std::cout << "Testare recompense:\n";
    auto& players = gameManager.getPlayers(); // Obține referința la jucători
    players[0].addReward(50); // Exemplu de recompensă
    std::cout << players[0].getName() << " are acum " << players[0].getScore() << " puncte.\n";

    // Inițializează serverul (opțional, dacă ai nevoie să sincronizezi schema bazei de date)
    initServer();

    // Pornește serverul cu funcționalitatea de multigaming
    startServerWithMultigaming();

    return 0;
}
