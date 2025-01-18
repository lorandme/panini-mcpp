#include "PlayerDisplay.h"
#include <iostream>

PlayerDisplay::PlayerDisplay(Player* player, const std::string& texturePrefix)
    : m_player(player) {
    for (int i = 0; i < 4; ++i) {
        std::string textureFile1 = texturePrefix + std::to_string(i + 1) + "_fr1.png";
        if (!m_texturesFrame1[i].loadFromFile(textureFile1)) {
            std::cerr << "Error loading texture: " << textureFile1 << std::endl;
            exit(EXIT_FAILURE);
        }

        std::string textureFile2 = texturePrefix + std::to_string(i + 1) + "_fr2.png";
        if (!m_texturesFrame2[i].loadFromFile(textureFile2)) {
            std::cerr << "Error loading texture: " << textureFile2 << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    m_sprite.setTexture(m_texturesFrame1[m_player->getId()]); 

    m_sprite.setScale(100.0f / 64.0f, 100.0f / 64.0f);
}

void PlayerDisplay::updateDisplay(float deltaTime) {
    m_animationTimer += deltaTime;

    if (m_animationTimer >= m_animationSpeed) {
        m_currentFrame = !m_currentFrame;

        m_animationTimer = 0.0f;

        if (m_currentFrame) {
            m_sprite.setTexture(m_texturesFrame2[m_player->getId()]);
        } else {
            m_sprite.setTexture(m_texturesFrame1[m_player->getId()]);
        }
    }
}

void PlayerDisplay::render(sf::RenderWindow& window) {
    auto position = m_player->getPosition();
    float tileSize = 80.0f;
    float playerSize = m_sprite.getGlobalBounds().width; 

    m_sprite.setPosition(
        static_cast<float>(position.first * tileSize + (tileSize - playerSize) / 2), 
        static_cast<float>(position.second * tileSize + (tileSize - playerSize) / 2)
    );

    window.draw(m_sprite);
}

void PlayerDisplay::updatePlayer(Player* player) {
    m_player = player;
}