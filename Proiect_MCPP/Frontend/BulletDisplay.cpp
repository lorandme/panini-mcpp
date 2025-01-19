#include "BulletDisplay.h"
#include <iostream>

BulletDisplay::BulletDisplay(Bullet* bullet) : m_bullet(bullet) {
    if (!m_texture.loadFromFile("../assets/fire.png")) {
        std::cerr << "Error loading bullet texture" << std::endl;
        exit(EXIT_FAILURE);
    }

    m_sprite.setTexture(m_texture);

    float scaleFactor = 10.0f / 8.0f;
    m_sprite.setScale(scaleFactor, scaleFactor);
}

void BulletDisplay::render(sf::RenderWindow& window) {
    auto position = m_bullet->getPosition();

    if (m_bullet->isBulletActive()) {
        float tileSize = 80.0f;

        float offsetX = 0.0f;
        float offsetY = 0.0f;

        switch (m_bullet->getDirection()) {
        case Direction::UP:
            offsetX = tileSize * 0.8f;
            break;
        case Direction::DOWN:
            offsetX = tileSize * 0.8f;
            break;
        case Direction::LEFT:
            offsetX = tileSize * 0.2f;
            break;
        case Direction::RIGHT:
            offsetX = tileSize * 0.7f;
            break;
        }

        m_sprite.setPosition(
            static_cast<float>(position.first * tileSize) + offsetX,
            static_cast<float>(position.second * tileSize) + offsetY
        );

        window.draw(m_sprite);
    }
}

void BulletDisplay::updateDisplay(float deltaTime) {
}