#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Bomb.h"

class BombDisplay {
public:
    BombDisplay(Bomb* bomb);
    void render(sf::RenderWindow& window, float deltaTime);
    float m_explosionTimer = 0.0f;
private:
    Bomb* m_bomb;
    sf::Texture m_bombTexture1;
    sf::Texture m_bombTexture2;
    sf::Texture m_explosionTexture;
    sf::Sprite m_sprite;
    float m_animationTimer;
    int m_currentFrame;
};