////#include "Client.h"
////#include <iostream>
////#include <string>
////
////int main() {
////    Client client("http://localhost:8080");
////
////    std::string username, password;
////    std::cout << "Introduceți username: ";
////    std::cin >> username;
////    std::cout << "Introduceți parola: ";
////    std::cin >> password;
////
////    cpr::Response response = client.registerUser(username, password);
////
////    if (response.status_code == 201) {
////        std::cout << "Înregistrare reusita!" << std::endl;
////    }
////    else {
////        std::cout << "Inregistrare esuata!" << std::endl;
////    }
////
////    return 0;
////}
//
////PROBA PENTRU BAZA DE DATE
//
//
//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/System.hpp>
//#include <cpr/cpr.h>
//#include <iostream>
//#include <string>
//
//// Function to create and return a text box
//sf::Text createTextBox(sf::Font& font, const std::string& placeholder, float x, float y) {
//    sf::Text textBox;
//    textBox.setFont(font);
//    textBox.setString(placeholder);
//    textBox.setCharacterSize(24);
//    textBox.setFillColor(sf::Color::Black);
//    textBox.setPosition(x, y);
//    return textBox;
//}
//
//// Client class to handle registration requests
//class Client {
//public:
//    Client(const std::string& server_url) : url(server_url) {}
//
//    cpr::Response registerUser(const std::string& username, const std::string& password) {
//        return cpr::Post(cpr::Url{ url + "/register" },
//            cpr::Payload{ {"username", username}, {"password", password} });
//    }
//
//private:
//    std::string url;
//};
//
//int main() {
//    // Create an SFML window
//    sf::RenderWindow window(sf::VideoMode(400, 300), "Registration");
//
//    // Load font for text display
//    sf::Font font;
//    if (!font.loadFromFile("arial.ttf")) {
//        std::cerr << "Error loading font!" << std::endl;
//        return -1;
//    }
//
//    // Create the UI elements (labels, textboxes, buttons)
//    sf::Text usernameLabel = createTextBox(font, "Username", 50, 50);
//    sf::Text passwordLabel = createTextBox(font, "Password", 50, 100);
//    sf::Text statusMessage("", font, 24);
//    statusMessage.setFillColor(sf::Color::Red);
//    statusMessage.setPosition(50, 200);
//
//    // Create textboxes for user input (just for visual, no actual text entry handling)
//    sf::Text usernameText("", font, 24);
//    usernameText.setFillColor(sf::Color::Black);
//    usernameText.setPosition(50, 70);
//
//    sf::Text passwordText("", font, 24);
//    passwordText.setFillColor(sf::Color::Black);
//    passwordText.setPosition(50, 120);
//
//    // Create the client object
//    Client client("http://localhost:8080");
//
//    // Main application loop
//    std::string username, password;
//    bool registering = false;
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//
//            // Handle keyboard input for username and password
//            if (event.type == sf::Event::TextEntered) {
//                if (registering) {
//                    continue;  // Avoid text input after registration is attempted
//                }
//                if (event.text.unicode < 128) {  // If it's a regular ASCII character
//                    char typedChar = static_cast<char>(event.text.unicode);
//                    if (event.text.unicode == 8 && !username.empty()) {  // Backspace
//                        username.pop_back();
//                    }
//                    else if (event.text.unicode == 8 && !password.empty()) {
//                        password.pop_back();
//                    }
//                    else if (username.length() < 20 && !registering) {  // Limit length for username
//                        username += typedChar;
//                    }
//                    else if (password.length() < 20 && !registering) {
//                        password += typedChar;
//                    }
//                }
//            }
//        }
//
//        // Display UI elements (labels, textboxes, etc.)
//        window.clear(sf::Color::White);
//        window.draw(usernameLabel);
//        window.draw(passwordLabel);
//        window.draw(usernameText);
//        window.draw(passwordText);
//        window.draw(statusMessage);
//
//        // Update the input text
//        usernameText.setString(username);
//        passwordText.setString(password);
//
//        // If the user presses Enter, attempt registration
//        if (!registering && !username.empty() && !password.empty()) {
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
//                registering = true;
//                cpr::Response response = client.registerUser(username, password);
//                if (response.status_code == 201) {
//                    statusMessage.setString("Registration Successful!");
//                    statusMessage.setFillColor(sf::Color::Green);
//                }
//                else {
//                    statusMessage.setString("Registration Failed!");
//                    statusMessage.setFillColor(sf::Color::Red);
//                }
//            }
//        }
//
//        window.display();
//    }
//
//    return 0;
//}


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "LoginScreen.h"
#include <iostream>

int main() {
    // Crearea unei ferestre de 800x600 pixeli
    sf::RenderWindow window(sf::VideoMode(800, 600), "Login Screen");

    try {
        // Crearea obiectului LoginScreen
        LoginScreen loginScreen(window);

        // Rularea ecranului de login
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