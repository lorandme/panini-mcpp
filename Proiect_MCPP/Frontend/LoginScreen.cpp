#include "LoginScreen.h"
#include <iostream>

LoginScreen::LoginScreen(sf::RenderWindow& window) : window(window) {
    if (!font.loadFromFile("../assets/arial.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    usernameLabel.setFont(font);
    usernameLabel.setString("Username:");
    usernameLabel.setCharacterSize(20);
    usernameLabel.setFillColor(sf::Color::White);
    usernameLabel.setPosition(50, 50);

    passwordLabel.setFont(font);
    passwordLabel.setString("Password:");
    passwordLabel.setCharacterSize(20);
    passwordLabel.setFillColor(sf::Color::White);
    passwordLabel.setPosition(50, 150);

    usernameBox.setSize({ 300, 40 });
    usernameBox.setPosition(50, 80);
    usernameBox.setFillColor(sf::Color::White);

    passwordBox.setSize({ 300, 40 });
    passwordBox.setPosition(50, 180);
    passwordBox.setFillColor(sf::Color::White);

    loginButton.setSize({ 150, 50 });
    loginButton.setPosition(125, 250);
    loginButton.setFillColor(sf::Color(57, 7, 115));

    loginButtonText.setFont(font);
    loginButtonText.setString("Login");
    loginButtonText.setCharacterSize(20);
    loginButtonText.setFillColor(sf::Color::White);
    loginButtonText.setPosition(175, 260);
}

void LoginScreen::run() {
    while (window.isOpen()) {
        processEvents();
        render();
    }
}

void LoginScreen::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        handleInput(event);
    }
}

void LoginScreen::render() {
    window.clear(sf::Color(50, 50, 50));

    window.draw(usernameLabel);
    window.draw(passwordLabel);

    drawTextBox(window, usernameBox, usernameInput);
    drawTextBox(window, passwordBox, isPasswordActive ? std::string(passwordInput.size(), '*') : passwordInput);

    window.draw(loginButton);
    window.draw(loginButtonText);

    window.display();
}

void LoginScreen::handleInput(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (usernameBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            isUsernameActive = true;
            isPasswordActive = false;
        }
        else if (passwordBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            isUsernameActive = false;
            isPasswordActive = true;
        }
        else if (loginButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            std::cout << "Login button clicked!\n";
            std::cout << "Username: " << usernameInput << "\n";
            std::cout << "Password: " << passwordInput << "\n";
        }
        else {
            isUsernameActive = false;
            isPasswordActive = false;
        }
    }

    if (event.type == sf::Event::TextEntered) {
        if (isUsernameActive && event.text.unicode < 128) {
            if (event.text.unicode == '\b' && !usernameInput.empty()) {
                usernameInput.pop_back();
            }
            else if (std::isprint(event.text.unicode)) {
                usernameInput += static_cast<char>(event.text.unicode);
            }
        }
        else if (isPasswordActive && event.text.unicode < 128) {
            if (event.text.unicode == '\b' && !passwordInput.empty()) {
                passwordInput.pop_back();
            }
            else if (std::isprint(event.text.unicode)) {
                passwordInput += static_cast<char>(event.text.unicode);
            }
        }
    }
}

void LoginScreen::drawTextBox(sf::RenderWindow& target, sf::RectangleShape& box, const std::string& text) {
    target.draw(box);

    sf::Text displayText;
    displayText.setFont(font);
    displayText.setString(text);
    displayText.setCharacterSize(20);
    displayText.setFillColor(sf::Color::Black);
    displayText.setPosition(box.getPosition().x + 5, box.getPosition().y + 5);

    target.draw(displayText);
}
