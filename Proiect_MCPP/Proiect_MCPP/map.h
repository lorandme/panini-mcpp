#pragma once

#include <vector>
#include <iostream>
#include "Tile.h"

class Map {
private:
    int m_width;
    int m_height;
    std::vector<std::vector<Tile>> m_grid;

public:
    Map(int width, int height);

    int getWidth() const;
    int getHeight() const;

    Tile& getTile(int x, int y);
    const Tile& getTile(int x, int y) const;
    void generateRandom();
    const std::vector<std::vector<Tile>>& getGrid() const;


    void printMap() const;
};