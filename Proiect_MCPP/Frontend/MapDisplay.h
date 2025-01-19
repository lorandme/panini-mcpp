#pragma once

#include <SFML/Graphics.hpp>
#include "Map.h"
#include "TileDisplay.h"

class MapDisplay {
public:
    MapDisplay(const Map& map, TileDisplay& tileDisplay);
    void draw(sf::RenderWindow& window);

private:
    const Map& m_map;
    TileDisplay& m_tileDisplay;
};
