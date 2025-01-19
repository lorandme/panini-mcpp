#include "PowerUpDisplay.h"
#include <iostream>

PowerUpDisplay::PowerUpDisplay(PowerUp* powerUp) : m_powerUp(powerUp) {
    std::string texturePath;

    switch (powerUp->getType()) {
    case PowerUp::EXTRA_HP:
        texturePath = "../assets/pwp_health.png";
        break;
    case PowerUp::SHIELD:
        texturePath = "../assets/pwp_shield.png";
        break;
    case PowerUp::SPEED_BOOST:
        texturePath = "../assets/pwp_speed.png";
        break;
    }

    if (!m_texture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load power-up texture: " << texturePath << std::endl;
        return;
    }

    m_sprite.setTexture(m_texture);
    m_sprite.setScale(2.0f, 2.0f);
}

void PowerUpDisplay::render(sf::RenderWindow& window) {
    const float tileSize = 80.0f;

    m_sprite.setPosition(
        m_powerUp->getX() * tileSize + tileSize / 2,
        m_powerUp->getY() * tileSize + tileSize / 2
    );

    sf::FloatRect spriteBounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(spriteBounds.width / 2, spriteBounds.height / 2);

    window.draw(m_sprite);
}