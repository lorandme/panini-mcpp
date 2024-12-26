//#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

// Define the Player struct
struct Player {
    std::string name;
    bool ready = false;
};

class LoginPage {
private:
    sf::RenderWindow& window;
    std::vector<Player> players;
    bool gameStarted = false;
    sf::Font font;
    sf::Text titleText;
    sf::Text infoText;
    sf::Text startGameText;
    sf::RectangleShape inputBox[4];
    sf::Text inputText[4];
    sf::Text inputPrompt[4];

    void handleInput();
    void render();
    bool areAllPlayersReady();

public:
    LoginPage(sf::RenderWindow& win);
    void run();
};
