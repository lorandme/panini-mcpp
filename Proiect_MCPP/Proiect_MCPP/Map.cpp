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
	return grid[x][y];
}

const Tile& Map::getTile(int x, int y) const {
    return grid[x][y];
}

//TODO: De imbunatatit metoda generateRandom pentru a asigura o cale accesibile pentru toti jucatorii
void Map::generateRandom() {
    srand(time(0)); 

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

	int edgeX = getHeight() - 1;
	int edgeY = getWidth() - 1;

	grid[0][0].setType(TileType::EMPTY);
	grid[0][edgeY].setType(TileType::EMPTY);
	grid[edgeX][0].setType(TileType::EMPTY);
	grid[edgeX][edgeY].setType(TileType::EMPTY);

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

