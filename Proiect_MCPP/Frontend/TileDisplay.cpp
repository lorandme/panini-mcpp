#include "TileDisplay.h"
#include <iostream>

TileDisplay::TileDisplay() {
    loadTextures();
}

void TileDisplay::loadTextures() {
    if (!m_textures[TileType::EMPTY].loadFromFile("../assets/empty.png")) {
        std::cerr << "Error loading texture for EMPTY tile" << std::endl;
    }
    if (!m_textures[TileType::WALL].loadFromFile("../assets/wall.png")) {
        std::cerr << "Error loading texture for WALL tile" << std::endl;
    }
    if (!m_textures[TileType::DESTRUCTIBLE_WALL].loadFromFile("../assets/destructible.png")) {
        std::cerr << "Error loading texture for DESTRUCTIBLE_WALL tile" << std::endl;
    }
}

void TileDisplay::drawTile(sf::RenderWindow& window, const Tile& tile, float x, float y) {
    sf::Sprite sprite;
    sprite.setTexture(getTextureForType(tile.getType()));
    sprite.setPosition(x, y);
    sprite.setScale(80.0f / sprite.getTexture()->getSize().x, 80.0f / sprite.getTexture()->getSize().y);
    window.draw(sprite);
}

sf::Texture& TileDisplay::getTextureForType(TileType type) {
    return m_textures[type];
}
