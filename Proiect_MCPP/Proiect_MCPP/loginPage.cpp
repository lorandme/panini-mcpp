#include "LoginPage.h"

const int MAX_PLAYERS = 4;

LoginPage::LoginPage(sf::RenderWindow& win) : window(win) {
    // Load font
    if (!font.loadFromFile("Arial.ttf")) {
        std::cerr << "Could not load font!" << std::endl;
        exit(1);
    }

    // Set up title
    titleText.setFont(font);
    titleText.setString("Battle City Multiplayer Game");
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(200.f, 50.f);

    // Set up information text
    infoText.setFont(font);
    infoText.setString("Enter Player Names:");
    infoText.setCharacterSize(30);
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition(300.f, 150.f);

    // Setup input boxes for 4 players
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        inputBox[i].setSize(sf::Vector2f(300.f, 50.f));
        inputBox[i].setFillColor(sf::Color::White);
        inputBox[i].setPosition(250.f, 250.f + i * 70.f);

        inputText[i].setFont(font);
        inputText[i].setString("");
        inputText[i].setCharacterSize(30);
        inputText[i].setFillColor(sf::Color::Black);
        inputText[i].setPosition(260.f, 260.f + i * 70.f);

        inputPrompt[i].setFont(font);
        inputPrompt[i].setString("Player " + std::to_string(i + 1) + ":");
        inputPrompt[i].setCharacterSize(30);
        inputPrompt[i].setFillColor(sf::Color::White);
        inputPrompt[i].setPosition(180.f, 250.f + i * 70.f);
    }

    // Setup "Start Game" text
    startGameText.setFont(font);
    startGameText.setString("Press ENTER to Start Game (4 Players)");
    startGameText.setCharacterSize(30);
    startGameText.setFillColor(sf::Color::Green);
    startGameText.setPosition(200.f, 500.f);
}

void LoginPage::handleInput() {
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace) && inputText[i].getString().getSize() > 0) {
            std::string str = inputText[i].getString();
            str.pop_back();
            inputText[i].setString(str);
        }

        for (char ch = 'A'; ch <= 'Z'; ++ch) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(ch))) {
                inputText[i].setString(inputText[i].getString() + ch);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && inputText[i].getString().getSize() > 0) {
            players[i].name = inputText[i].getString();
            players[i].ready = true;
        }
    }
}

void LoginPage::render() {
    window.clear();
    window.draw(titleText);
    window.draw(infoText);

    for (int i = 0; i < MAX_PLAYERS; ++i) {
        window.draw(inputBox[i]);
        window.draw(inputText[i]);
        window.draw(inputPrompt[i]);
    }

    if (gameStarted) {
        window.draw(startGameText);
    }

    window.display();
}

bool LoginPage::areAllPlayersReady() {
    for (auto& player : players) {
        if (player.name.empty() || !player.ready) {
            return false;
        }
    }
    return true;
}

void LoginPage::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        handleInput();

        if (areAllPlayersReady()) {
            startGameText.setString("All players are ready! Press ENTER to start!");
            gameStarted = true;
        }

        render();
    }
}
#pragma once
