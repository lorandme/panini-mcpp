#include "map.h"
#include "tile.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Map::Map(int width, int height)
    : m_width(width), m_height(height), m_grid(width, std::vector<Tile>(height)) {
    generateRandom();
}

int Map::getWidth() const {
    return m_width;
}

int Map::getHeight() const {
    return m_height;
}

Tile& Map::getTile(int x, int y) {
    if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
        throw std::out_of_range("Tile coordinates out of bounds");
    }
    return m_grid[x][y];
}

const Tile& Map::getTile(int x, int y) const {
    if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
        throw std::out_of_range("Tile coordinates out of bounds");
    }
    return m_grid[x][y];
}

void Map::generateRandom() {
	srand(static_cast<unsigned int>(time(0)));
	//static_cast<unsigned int>(time(0)) - converteste timpul in secunde in unsigned int

    int emptyPercentage = 60;
    int wallPercentage = 20;
    int destructibleWallPercentage = 10;

    for (int x = 0; x < m_width; ++x) {
        for (int y = 0; y < m_height; ++y) {
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

            m_grid[x][y] = Tile(type);
        }
    }

    m_grid[0][0].setType(TileType::EMPTY);
    m_grid[0][m_height - 1].setType(TileType::EMPTY);
    m_grid[m_width - 1][0].setType(TileType::EMPTY);
    m_grid[m_width - 1][m_height - 1].setType(TileType::EMPTY);
}

void Map::printMap() const {
    for (int x = 0; x < m_width; ++x) {
        for (int y = 0; y < m_height; ++y) {
            const Tile& tile = m_grid[x][y];
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