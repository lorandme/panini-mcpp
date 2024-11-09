#pragma once

#include <vector>
#include <random>
#include <iostream>

class Map {
private:
    int width;
    int height;
    std::vector<std::vector<Tile>> grid;

public:
    Map(int width, int height) : width(width), height(height), grid(height, std::vector<Tile>(width)) {
        generateRandom();
    }

    int getWidth() const { return width; }

    int getHeight() const { return height; }

    Tile& getTile(int x, int y) {
        return grid[y][x];
    }

    void generateRandom() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 3); // 0 - Empty, 1 - IndestructibleWall, 2 - DestructibleWall, 3 - Bomb

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                TileType tileType = static_cast<TileType>(dis(gen));
                grid[y][x] = Tile(tileType);
            }
        }
    }

    // Afișează harta pe consolă (pentru testare)
    void printMap() const {
        for (const auto& row : grid) {
            for (const auto& tile : row) {
                switch (tile.type) {
                case TileType::Empty:            std::cout << "."; break;
                case TileType::IndestructibleWall: std::cout << "#"; break;
                case TileType::DestructibleWall:  std::cout << "D"; break;
                case TileType::Bomb:              std::cout << "B"; break;
                }
            }
            std::cout << "\n";
        }
    }
};
