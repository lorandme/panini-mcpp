#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>
#include <unordered_map>

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
    sf::Color color;
    sf::Keyboard::Key up, down, left, right;
    sf::Keyboard::Key lastDirection;
    float shootCooldown = 0.3f;
    float timeSinceLastShot = 0.0f;
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
        {1, sf::Vector2f(100, 100), sf::Color::Blue, sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W},
        {2, sf::Vector2f(200, 100), sf::Color::Red, sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up},
        {3, sf::Vector2f(100, 200), sf::Color::Yellow, sf::Keyboard::I, sf::Keyboard::K, sf::Keyboard::J, sf::Keyboard::L, sf::Keyboard::I},
        {4, sf::Vector2f(200, 200), sf::Color::Green, sf::Keyboard::Numpad8, sf::Keyboard::Numpad5, sf::Keyboard::Numpad4, sf::Keyboard::Numpad6, sf::Keyboard::Numpad8}
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

        if (player.id==1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.timeSinceLastShot >= player.shootCooldown) {
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

void renderMap(sf::RenderWindow& window) {
    for (size_t y = 0; y < mockMap.size(); ++y) {
        for (size_t x = 0; x < mockMap[y].size(); ++x) {
            sf::RectangleShape tile(sf::Vector2f(80, 80));
            tile.setPosition(x * 80, y * 80);

            switch (mockMap[y][x]) {
            case TileType::Wall:
                tile.setFillColor(sf::Color::White);
                break;
            case TileType::DestructibleWall:
                tile.setFillColor(sf::Color::Magenta);
                break;
            case TileType::Empty:
                tile.setFillColor(sf::Color::Black);
                break;
            }

            window.draw(tile);
        }
    }
}

void renderGameState(sf::RenderWindow& window, const GameState& state) {
    for (const auto& player : state.players) {
        sf::RectangleShape playerShape(sf::Vector2f(25, 40));
        playerShape.setFillColor(player.color);
        playerShape.setPosition(player.position);
        window.draw(playerShape);
    }

    for (const auto& bullet : state.bullets) {
        sf::RectangleShape bulletShape(sf::Vector2f(10, 10));
        bulletShape.setFillColor(sf::Color::Yellow);
        bulletShape.setPosition(bullet.position);
        window.draw(bulletShape);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mock Test");
    GameState state = mockGameState();
    generateMockMap();

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        handleInput(state, deltaTime);
        updateBullets(state, deltaTime);

        window.clear();
        renderMap(window);
        renderGameState(window, state);
        window.display();
    }

    return 0;
}
