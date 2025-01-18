#pragma once

#include <SFML/Graphics.hpp>
#include "Bullet.h"

class BulletDisplay {
private:
    Bullet* m_bullet;
    sf::Texture m_texture;
    sf::Sprite m_sprite;

public:
    BulletDisplay(Bullet* bullet);

    void render(sf::RenderWindow& window);
    void updateDisplay(float deltaTime);
};

