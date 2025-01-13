//#include <SFML/Graphics.hpp>
//#include <vector>
//#include <unordered_map>
//#include <iostream>
//#include "LoginPage.h"
//#include <chrono>
//
//enum class TileType {
//    Empty,
//    Wall,
//    DestructibleWall,
//    PowerUp,  // Adăugat un tip nou de tile pentru power-ups
//    Enemy
//};
//
//const int mapWidth = 10;
//const int mapHeight = 8;
//
//std::vector<std::vector<TileType>> mockMap(mapHeight, std::vector<TileType>(mapWidth, TileType::Empty));
//
//static void generateMockMap() {
//    for (int y = 0; y < mapHeight; ++y) {
//        for (int x = 0; x < mapWidth; ++x) {
//            if (x == 0 || y == 0 || x == mapWidth - 1 || y == mapHeight - 1) {
//                mockMap[y][x] = TileType::Wall;
//            }
//            else if (x == 4 && y == 3) {
//                mockMap[y][x] = TileType::DestructibleWall;
//            }
//            else if (x == 5 && y == 5) {
//                mockMap[y][x] = TileType::PowerUp;  // Power-up pe hartă
//            }
//        }
//    }
//}
//
//struct Player {
//    int id;
//    sf::Vector2f position;
//    sf::Color color;
//    sf::Keyboard::Key up, down, left, right;
//    sf::Keyboard::Key lastDirection;
//    float shootCooldown = 0.3f;
//    float timeSinceLastShot = 0.0f;
//    int score = 0;  // Scorul jucătorului
//};
//
//struct Bullet {
//    sf::Vector2f position;
//    sf::Vector2f direction;
//    float speed = 400.0f;
//    float timeAlive = 0.0f;
//
//    void update(float deltaTime) {
//        position += direction * speed * deltaTime;
//        timeAlive += deltaTime;
//    }
//
//    bool isAlive() const {
//        return timeAlive < 5.0f;
//    }
//};
//
//struct GameState {
//    std::vector<Player> players;
//    std::vector<Bullet> bullets;
//};
//
//GameState mockGameState() {
//    GameState state;
//
//    state.players = {
//        {1, sf::Vector2f(100, 100), sf::Color::Blue, sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W},
//        {2, sf::Vector2f(200, 100), sf::Color::Red, sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up},
//        {3, sf::Vector2f(100, 200), sf::Color::Yellow, sf::Keyboard::I, sf::Keyboard::K, sf::Keyboard::J, sf::Keyboard::L, sf::Keyboard::I},
//        {4, sf::Vector2f(200, 200), sf::Color::Green, sf::Keyboard::Numpad8, sf::Keyboard::Numpad5, sf::Keyboard::Numpad4, sf::Keyboard::Numpad6, sf::Keyboard::Numpad8}
//    };
//    return state;
//}
//
//static void handleInput(GameState& state, float deltaTime) {
//    float speed = 300.0f;
//
//    std::unordered_map<sf::Keyboard::Key, sf::Vector2f> directionMap = {
//        {sf::Keyboard::W, {0, -1}},
//        {sf::Keyboard::S, {0, 1}},
//        {sf::Keyboard::A, {-1, 0}},
//        {sf::Keyboard::D, {1, 0}},
//        {sf::Keyboard::Up, {0, -1}},
//        {sf::Keyboard::Down, {0, 1}},
//        {sf::Keyboard::Left, {-1, 0}},
//        {sf::Keyboard::Right, {1, 0}}
//    };
//
//    for (auto& player : state.players) {
//        if (sf::Keyboard::isKeyPressed(player.up)) {
//            player.position.y -= speed * deltaTime;
//            player.lastDirection = player.up;
//        }
//        if (sf::Keyboard::isKeyPressed(player.down)) {
//            player.position.y += speed * deltaTime;
//            player.lastDirection = player.down;
//        }
//        if (sf::Keyboard::isKeyPressed(player.left)) {
//            player.position.x -= speed * deltaTime;
//            player.lastDirection = player.left;
//        }
//        if (sf::Keyboard::isKeyPressed(player.right)) {
//            player.position.x += speed * deltaTime;
//            player.lastDirection = player.right;
//        }
//
//        player.timeSinceLastShot += deltaTime;
//
//        if (player.id == 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.timeSinceLastShot >= player.shootCooldown) {
//            Bullet newBullet;
//            newBullet.position = player.position;
//            newBullet.direction = directionMap[player.lastDirection];
//            state.bullets.push_back(newBullet);
//            player.timeSinceLastShot = 0.0f;
//        }
//    }
//}
//
//static void updateBullets(GameState& state, float deltaTime) {
//    for (auto it = state.bullets.begin(); it != state.bullets.end(); ) {
//        it->update(deltaTime);
//
//         Dacă proiectilul a ieșit din viață sau a lovit un perete, elimină-l
//        if (!it->isAlive() || checkCollision(it->position)) {
//            it = state.bullets.erase(it);  // Șterge proiectilul din listă
//        }
//        else {
//            ++it;
//        }
//    }
//}
//
//static void renderMap(sf::RenderWindow& window) {
//    for (size_t y = 0; y < mockMap.size(); ++y) {
//        for (size_t x = 0; x < mockMap[y].size(); ++x) {
//            sf::RectangleShape tile(sf::Vector2f(80, 80));
//            tile.setPosition(x * 80, y * 80);
//
//            switch (mockMap[y][x]) {
//            case TileType::Wall:
//                tile.setFillColor(sf::Color::White);
//                break;
//            case TileType::DestructibleWall:
//                tile.setFillColor(sf::Color::Magenta);
//                break;
//            case TileType::Empty:
//                tile.setFillColor(sf::Color::Black);
//                break;
//            case TileType::PowerUp:
//                tile.setFillColor(sf::Color::Green); // Power-up de culoare verde
//                break;
//            }
//
//            window.draw(tile);
//        }
//    }
//}
//
//static void renderGameState(sf::RenderWindow& window, const GameState& state) {
//    for (const auto& player : state.players) {
//        sf::RectangleShape playerShape(sf::Vector2f(25, 40));
//        playerShape.setFillColor(player.color);
//        playerShape.setPosition(player.position);
//        window.draw(playerShape);
//    }
//
//    for (const auto& bullet : state.bullets) {
//        sf::RectangleShape bulletShape(sf::Vector2f(10, 10));
//        bulletShape.setFillColor(sf::Color::Yellow);
//        bulletShape.setPosition(bullet.position);
//        window.draw(bulletShape);
//    }
//}
//
//void renderScores(sf::RenderWindow& window, const std::vector<Player>& players) {
//    sf::Font font;
//    if (!font.loadFromFile("arial.ttf")) {  // Încarcă fontul
//        std::cout << "Failed to load font!" << std::endl;
//        return;  // Dacă nu reușește să încarce fontul
//    }
//
//    for (const auto& player : players) {
//        sf::Text scoreText;
//        scoreText.setFont(font);
//        scoreText.setString("Player " + std::to_string(player.id) + ": " + std::to_string(player.score));
//        scoreText.setPosition(10, 10 + player.id * 30);  // Poziția textului pe ecran
//        window.draw(scoreText);
//    }
//}
//
//bool checkCollision(const sf::Vector2f& newPosition) {
//    int x = static_cast<int>(newPosition.x / 80);
//    int y = static_cast<int>(newPosition.y / 80);
//
//    if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight) {
//        return true; // Dacă este în afara hărții
//    }
//
//    return mockMap[y][x] == TileType::Wall;
//}
//
//int main() {
//    sf::RenderWindow window(sf::VideoMode(800, 600), "Game with Login");
//    LoginPage loginPage(window);
//    loginPage.run();
//
//    std::vector<Player> players = loginPage.getPlayers();
//
//    if (players.empty()) {
//        std::cout << "Login process terminated or window closed." << std::endl;
//        return 1;
//    }
//
//    std::cout << "Players logged in:" << std::endl;
//    for (const auto& player : players) {
//        std::cout << "Player: " << player.id << std::endl;
//    }
//
//    GameState state = mockGameState();
//    generateMockMap();
//
//    sf::Clock clock;
//    bool isPaused = false;
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
//            isPaused = !isPaused;
//            sf::sleep(sf::seconds(0.2f)); // Delay pentru a preveni comutarea rapidă
//        }
//
//        float deltaTime = clock.restart().asSeconds();
//
//        window.clear();
//
//        if (!isPaused) {
//            handleInput(state, deltaTime);
//            updateBullets(state, deltaTime);
//            renderMap(window);
//            renderGameState(window, state);
//            renderScores(window, players);
//        }
//        else {
//            sf::Font font;
//            if (!font.loadFromFile("arial.ttf")) {
//                std::cout << "Failed to load font!" << std::endl;
//                return 1;
//            }
//            sf::Text pauseText("Game Paused", font, 30);
//            pauseText.setFillColor(sf::Color::Red);
//            pauseText.setPosition(300, 250);
//            window.draw(pauseText);
//        }
//
//        window.display();
//    }
//
//    return 0;
//}
//
//
////!!! MOCK TEST PENTRU INTERFATA GRAFICA !!!
////
#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>
#include <unordered_map>
//#include "Database.h"

enum class TileType {
    Empty,
    Wall,
    DestructibleWall
};

const int mapWidth = 10;
const int mapHeight = 8;

std::vector<std::vector<TileType>> mockMap(mapHeight, std::vector<TileType>(mapWidth, TileType::Empty));

void generateMockMap() {
    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            if (x == 0 || y == 0 || x == mapWidth - 1 || y == mapHeight - 1) {
                mockMap[y][x] = TileType::Wall;
            }
            else if (x == 4 && y == 3) {
                mockMap[y][x] = TileType::DestructibleWall;
            }
        }
    }
}

struct Player {
    int id;
    sf::Vector2f position;
    sf::Keyboard::Key up, down, left, right;
    sf::Keyboard::Key lastDirection;
    float shootCooldown = 0.3f;
    float timeSinceLastShot = 0.0f;

    /* Add frame switching logic*/
    float frameTimer = 0.0f;  // Timer to switch frames
    bool isFrame1 = true;      // Indicates if the current frame is the first one
};

struct Bullet {
    sf::Vector2f position;
    sf::Vector2f direction;
    float speed = 400.0f;
    float timeAlive = 0.0f;

    void update(float deltaTime) {
        position += direction * speed * deltaTime;
        timeAlive += deltaTime;
    }

    bool isAlive() const {
        return timeAlive < 5.0f;
    }
};

struct GameState {
    std::vector<Player> players;
    std::vector<Bullet> bullets;
};

GameState mockGameState() {
    GameState state;

    state.players = {
        {1, sf::Vector2f(100, 100), sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W},
        {2, sf::Vector2f(200, 100), sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up},
        {3, sf::Vector2f(100, 200), sf::Keyboard::I, sf::Keyboard::K, sf::Keyboard::J, sf::Keyboard::L, sf::Keyboard::I},
        {4, sf::Vector2f(200, 200), sf::Keyboard::Numpad8, sf::Keyboard::Numpad5, sf::Keyboard::Numpad4, sf::Keyboard::Numpad6, sf::Keyboard::Numpad8}
    };
    return state;
}

void handleInput(GameState& state, float deltaTime) {
    float speed = 300.0f;

    std::unordered_map<sf::Keyboard::Key, sf::Vector2f> directionMap = {
        {sf::Keyboard::W, {0, -1}},
        {sf::Keyboard::S, {0, 1}},
        {sf::Keyboard::A, {-1, 0}},
        {sf::Keyboard::D, {1, 0}},
        {sf::Keyboard::Up, {0, -1}},
        {sf::Keyboard::Down, {0, 1}},
        {sf::Keyboard::Left, {-1, 0}},
        {sf::Keyboard::Right, {1, 0}}
    };

    for (auto& player : state.players) {
        if (sf::Keyboard::isKeyPressed(player.up)) {
            player.position.y -= speed * deltaTime;
            player.lastDirection = player.up;
        }
        if (sf::Keyboard::isKeyPressed(player.down)) {
            player.position.y += speed * deltaTime;
            player.lastDirection = player.down;
        }
        if (sf::Keyboard::isKeyPressed(player.left)) {
            player.position.x -= speed * deltaTime;
            player.lastDirection = player.left;
        }
        if (sf::Keyboard::isKeyPressed(player.right)) {
            player.position.x += speed * deltaTime;
            player.lastDirection = player.right;
        }

        player.timeSinceLastShot += deltaTime;
        player.frameTimer += deltaTime;  // Increment frame timer

        if (player.frameTimer >= 0.5f) {  // Switch frame every 1 second
            player.isFrame1 = !player.isFrame1;
            player.frameTimer = 0.0f;
        }

        if (player.id == 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.timeSinceLastShot >= player.shootCooldown) {
            Bullet newBullet;
            newBullet.position = player.position;
            newBullet.direction = directionMap[player.lastDirection];
            state.bullets.push_back(newBullet);
            player.timeSinceLastShot = 0.0f;
        }
    }
}

void updateBullets(GameState& state, float deltaTime) {
    for (auto& bullet : state.bullets) {
        bullet.update(deltaTime);
    }
}

void renderMap(sf::RenderWindow& window, sf::Texture& wallTexture, sf::Texture& destructibleWallTexture, sf::Texture& emptyTileTexture) {
    for (size_t y = 0; y < mockMap.size(); ++y) {
        for (size_t x = 0; x < mockMap[y].size(); ++x) {
            sf::Sprite tileSprite;

            switch (mockMap[y][x]) {
            case TileType::Wall:
                tileSprite.setTexture(wallTexture);
                break;
            case TileType::DestructibleWall:
                tileSprite.setTexture(destructibleWallTexture);
                break;
            case TileType::Empty:
                tileSprite.setTexture(emptyTileTexture);
                break;
            }

            tileSprite.setPosition(x * 80, y * 80);
            tileSprite.setScale(80.0f / 32.0f, 80.0f / 32.0f); // Scale texture to 80x80
            window.draw(tileSprite);
        }
    }
}

void renderGameState(sf::RenderWindow& window, const GameState& state, sf::Texture playerTextures[8], sf::Texture& bulletTexture) {
    for (size_t i = 0; i < state.players.size(); ++i) {
        const auto& player = state.players[i];
        sf::Sprite playerSprite;

        if (player.isFrame1) {
            playerSprite.setTexture(playerTextures[i * 2]);  // Use frame 1 (pl1_fr1.png, pl2_fr1.png, etc.)
        }
        else {
            playerSprite.setTexture(playerTextures[i * 2 + 1]);  // Use frame 2 (pl1_fr2.png, pl2_fr2.png, etc.)
        }

        playerSprite.setPosition(player.position);

        playerSprite.setScale(100.0f / 64.0f, 100.0f / 64.0f);  // Scaling player to fit the 80x80 tiles
        window.draw(playerSprite);
    }

    for (const auto& bullet : state.bullets) {
        sf::Sprite bulletSprite;
        bulletSprite.setTexture(bulletTexture);
        bulletSprite.setPosition(bullet.position);

        bulletSprite.setScale(16.0f / bulletTexture.getSize().x, 16.0f / bulletTexture.getSize().y);

        window.draw(bulletSprite);
    }
}

//#include <iostream>
//#include "../Proiect_MCPP/database.h"
//
//void testDatabaseOperations() {
//    Database db;
//
//    // Deschide baza de date
//    if (db.open("game_database.db")) {
//        std::cout << "Baza de date a fost deschisă cu succes!" << std::endl;
//
//        // Adaugă utilizatori
//        if (db.addUser("player1", "1234")) {
//            std::cout << "Utilizator adăugat cu succes!" << std::endl;
//        }
//        else {
//            std::cerr << "Eroare la adăugarea utilizatorului!" << std::endl;
//        }
//
//        // Autentificare
//        if (db.authenticateUser("player1", "1234")) {
//            std::cout << "Autentificare reușită!" << std::endl;
//        }
//        else {
//            std::cerr << "Eșec la autentificare!" << std::endl;
//        }
//    }
//    else {
//        std::cerr << "Nu s-a putut deschide baza de date!" << std::endl;
//    }
//
//    db.close();
//}

#include "LoginScreen.h";
#include <iostream>
int main() {

    sf::RenderWindow window(sf::VideoMode(400, 400), "Login Screen", sf::Style::Close);

    try {
        LoginScreen loginScreen(window);
        loginScreen.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    // Apelează funcțiile de test ale serverului
//    testDatabaseOperations();
//    
//    sf::RenderWindow window(sf::VideoMode(800, 600), "Mock Test");
//
//    sf::Texture wallTexture, destructibleWallTexture, emptyTileTexture, bulletTexture;
//    sf::Texture playerTextures[8];  // 4 players, each having 2 frames
//
//    if (!wallTexture.loadFromFile("../assets/wall.png") ||
//        !destructibleWallTexture.loadFromFile("../assets/destructible.png") ||
//        !emptyTileTexture.loadFromFile("../assets/empty.png") ||
//        !bulletTexture.loadFromFile("../assets/fire.png") || // Load fire.png for bullets
//        !playerTextures[0].loadFromFile("../assets/pl1_fr1.png") ||
//        !playerTextures[1].loadFromFile("../assets/pl1_fr2.png") ||
//        !playerTextures[2].loadFromFile("../assets/pl2_fr1.png") ||
//        !playerTextures[3].loadFromFile("../assets/pl2_fr2.png") ||
//        !playerTextures[4].loadFromFile("../assets/pl3_fr1.png") ||
//        !playerTextures[5].loadFromFile("../assets/pl3_fr2.png") ||
//        !playerTextures[6].loadFromFile("../assets/pl4_fr1.png") ||
//        !playerTextures[7].loadFromFile("../assets/pl4_fr2.png")) {
//        return -1;
//    }
//
//    GameState state = mockGameState();
//    generateMockMap();
//
//    sf::Clock clock;
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        float deltaTime = clock.restart().asSeconds();
//
//        handleInput(state, deltaTime);
//        updateBullets(state, deltaTime);
//
//        window.clear();
//        renderMap(window, wallTexture, destructibleWallTexture, emptyTileTexture);
//        renderGameState(window, state, playerTextures, bulletTexture);
//        window.display();
//    }

    return 0;
}
 
//}
//#include <iostream>
//#include "Client.h"
//#include <nlohmann/json.hpp>
//
//int main() {
//    // Define server IP and port
//    std::string serverIP = "127.0.0.1"; // Localhost for testing
//    int serverPort = 8080;
//
//    // Initialize the Client
//    Client client(serverIP, serverPort);
//
//    try {
//        client.init(); // Initialize socket and connect to the server
//        std::cout << "Connected to the server at " << serverIP << ":" << serverPort << std::endl;
//
//        // Create a sample request to send to the server
//        nlohmann::json request = {
//            {"type", "test"},
//            {"message", "Hello, server!"}
//        };
//
//        // Send the request
//        client.sendMessage(request);
//        std::cout << "Message sent to the server: " << request.dump() << std::endl;
//
//        // Receive the server's response
//        nlohmann::json response = client.receiveMessage();
//        std::cout << "Response received from server: " << response.dump() << std::endl;
//
//    }
//    catch (const std::exception& e) {
//        std::cerr << "Error: " << e.what() << std::endl;
//    }
//
//    return 0;
//}
