#include "Map.h"
#include <vector>
#include <iostream>

Map::Map(int width, int height) : width(width), height(height), grid(width, std::vector<Tile*>(height, nullptr)) {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            grid[i][j] = nullptr;
        }
    }
}

Map::~Map() {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            delete grid[i][j]; // 동적 할당한 Tile 객체 메모리 해제
        }
    }
}

void Map::draw(RenderWindow& window) {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            grid[i][j]->draw(window);
        }
    }
}

Tile::Tile(float x, float y, float width, float height, const std::string& textureFile) {
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, height));
    if (!texture.loadFromFile(textureFile)) {
        std::cout << "Failed to load texture from " << textureFile << std::endl;
    }
    shape.setTexture(&texture);
}

void Tile::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

Grass::Grass(float x, float y, float width, float height) : Tile(x, y, width, height, "grass1.png") {

}

Road::Road(float x, float y, float width, float height) : Tile(x, y, width, height, "Concrete1.png") {

}