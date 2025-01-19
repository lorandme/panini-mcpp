#include "MapDisplay.h"

MapDisplay::MapDisplay(const Map& map, TileDisplay& tileDisplay)
    : m_map(map), m_tileDisplay(tileDisplay) {
}

void MapDisplay::draw(sf::RenderWindow& window) {
    for (int y = 0; y < m_map.getHeight(); ++y) {
        for (int x = 0; x < m_map.getWidth(); ++x) {
            const Tile& tile = m_map.getTile(x, y);
            m_tileDisplay.drawTile(window, tile, x * 80, y * 80);
        }
    }
}
