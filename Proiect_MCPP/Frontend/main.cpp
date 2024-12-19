
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "LoginScreen.h"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Login Screen");

    try {
        LoginScreen loginScreen(window);

        loginScreen.run();
    }
    catch (const std::runtime_error& e) {
        std::cout<< "Eroare: " << e.what() << std::endl;
    }

    return 0;
}


/*de integrat

#include "GameManager.h"

int main() {
    const int mapWidth = 15;
    const int mapHeight = 10;
    const float tileSize = 80.0f;

    GameManager game(mapWidth, mapHeight, tileSize);
    game.run();

    return 0;
}*/