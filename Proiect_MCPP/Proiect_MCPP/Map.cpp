#include "map.h"
#include "tile.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Map::Map(int width, int height)
    : width(width), height(height), grid(width, std::vector<Tile>(height)) {
    generateRandom();
}

int Map::getWidth() const {
    return width;
}

int Map::getHeight() const {
    return height;
}

Tile& Map::getTile(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Tile coordinates out of bounds");
    }
    return grid[x][y];
}

const Tile& Map::getTile(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Tile coordinates out of bounds");
    }
    return grid[x][y];
}

void Map::generateRandom() {
	srand(static_cast<unsigned int>(time(0)));
	//static_cast<unsigned int>(time(0)) - converteste timpul in secunde in unsigned int

    int emptyPercentage = 60;
    int wallPercentage = 20;
    int destructibleWallPercentage = 10;

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            int randValue = rand() % 100;

            TileType type;
            if (randValue < emptyPercentage) {
                type = TileType::EMPTY;
            }
            else if (randValue < emptyPercentage + wallPercentage) {
                type = TileType::WALL;
            }
            else {
                type = TileType::DESTRUCTIBLE_WALL;
            }

            grid[x][y] = Tile(type);
        }
    }

    grid[0][0].setType(TileType::EMPTY);
    grid[0][height - 1].setType(TileType::EMPTY);
    grid[width - 1][0].setType(TileType::EMPTY);
    grid[width - 1][height - 1].setType(TileType::EMPTY);
}

void Map::printMap() const {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            const Tile& tile = grid[x][y];
            switch (tile.getType()) {
            case TileType::EMPTY:
                std::cout << "E";
                break;
            case TileType::WALL:
                std::cout << "W";
                break;
            case TileType::DESTRUCTIBLE_WALL:
                std::cout << "D";
                break;
            }
        }
        std::cout << "\n";
    }
}