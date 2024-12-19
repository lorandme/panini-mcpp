#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class LoginScreen {
public:
    LoginScreen(sf::RenderWindow& window);
    void run();

private:
    sf::RenderWindow& window;
    sf::Font font;

    sf::Text usernameLabel;
    sf::Text passwordLabel;
    sf::RectangleShape usernameBox;
    sf::RectangleShape passwordBox;
    sf::RectangleShape loginButton;
    sf::RectangleShape registerButton;
    sf::Text loginButtonText;
    sf::Text registerButtonText;
    sf::Text statusMessage;

    std::string usernameInput;
    std::string passwordInput;
    bool isUsernameActive = false;
    bool isPasswordActive = false;

    void processEvents();
    void render();
    void handleInput(sf::Event& event);
    void drawTextBox(sf::RenderWindow& target, sf::RectangleShape& box, const std::string& text);
    void handleLogin();
    void handleRegister();
};