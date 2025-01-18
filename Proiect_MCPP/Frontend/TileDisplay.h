#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include "Tile.h"

class TileDisplay {
public:
    TileDisplay();
    void drawTile(sf::RenderWindow& window, const Tile& tile, float x, float y);

private:
    std::map<TileType, sf::Texture> m_textures;
    void loadTextures();
    sf::Texture& getTextureForType(TileType type);
};
