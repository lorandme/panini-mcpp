#pragma once

#include <vector>
#include <random>
#include <iostream>
#include "tile.h"

class Map {
private:
    int width;
    int height;
    std::vector<std::vector<Tile>> grid;
public:
    Map(int width, int height);

    int getWidth() const;
    int getHeight() const;

    Tile& getTile(int x, int y);
    const Tile& getTile(int x, int y) const;  // Supraincarcare pentru obiecte const
    void generateRandom();

    void printMap() const;
      
    
};
