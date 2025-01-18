#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include <string>

class PlayerDisplay {
private:
    Player* m_player;

    sf::Texture m_texturesFrame1[4];
    sf::Texture m_texturesFrame2[4];
    sf::Sprite m_sprite;

    bool m_currentFrame = false;
    float m_animationTimer = 0.0f;
    const float m_animationSpeed = 0.5f;

public:
    PlayerDisplay(Player* player, const std::string& texturePrefix);

    void updateDisplay(float deltaTime);
    void render(sf::RenderWindow& window);
    void updatePlayer(Player* player);

    sf::Sprite& getSprite() { return m_sprite; }
};