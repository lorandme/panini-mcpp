#include "BombDisplay.h"
#include <iostream>

BombDisplay::BombDisplay(Bomb* bomb) :
    m_bomb(bomb),
    m_animationTimer(0.0f),
    m_currentFrame(0) {
    if (!m_bombTexture1.loadFromFile("../assets/bomb_f1.png")) {
        std::cerr << "Failed to load bomb frame 1 texture" << std::endl;
    }
    if (!m_bombTexture2.loadFromFile("../assets/bomb_f2.png")) {
        std::cerr << "Failed to load bomb frame 2 texture" << std::endl;
    }

    m_sprite.setTexture(m_bombTexture1);
    m_sprite.setScale(4.0f, 4.0f);
}

void BombDisplay::render(sf::RenderWindow& window, float deltaTime) {
    const float tileSize = 80.0f;

    m_animationTimer += deltaTime;

    if (m_animationTimer >= 0.25f) {
        m_currentFrame = 1 - m_currentFrame;
        m_animationTimer = 0.0f;
    }

    m_sprite.setTexture(m_currentFrame == 0 ? m_bombTexture1 : m_bombTexture2);
    m_sprite.setScale(52.0f / 16.0f, 52.0f / 16.0f);

    sf::FloatRect spriteBounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(spriteBounds.width / 2, spriteBounds.height / 2);
    m_sprite.setPosition(
        m_bomb->getX() * tileSize + tileSize / 2,
        m_bomb->getY() * tileSize + tileSize / 2
    );

    window.draw(m_sprite);
}