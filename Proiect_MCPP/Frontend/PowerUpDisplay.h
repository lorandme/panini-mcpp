#pragma once
#include <SFML/Graphics.hpp>
#include "PowerUp.h"

class PowerUpDisplay {
private:
    PowerUp* m_powerUp;
    sf::Sprite m_sprite;
    sf::Texture m_texture;

public:
    PowerUpDisplay(PowerUp* powerUp);
    void render(sf::RenderWindow& window);
};

