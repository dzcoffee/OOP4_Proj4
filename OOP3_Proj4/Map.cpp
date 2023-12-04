#include "Map.h"
#include <vector>
#include <iostream>

// Map
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

// Tile
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

// PlayerTile
PlayerTile::PlayerTile(float x, float y, float width, float height, Player& player) : Tile(x, y, width, height, "puang.png"), player(player) {

}

bool PlayerTile::onCollision(Player& player) {
    return false;
}

void PlayerTile::move(float x, float y) {
    shape.setPosition(x, y);
}

Player& PlayerTile::getPlayer() {
    return player;
}

int PlayerTile::getDirection() {
    return direction;
}

void PlayerTile::inverse() {
    direction = -direction;
    if (direction < 0)
        shape.setTextureRect(sf::IntRect(0, 0, 64, 64));
    else
        shape.setTextureRect(sf::IntRect(64, 0, -64, 64));
}

// Grass
Grass::Grass(float x, float y, float width, float height) : Tile(x, y, width, height, "grass1.png") {

}

bool Grass::onCollision(Player& player) {

    return true;
}

// Road
Road::Road(float x, float y, float width, float height) : Tile(x, y, width, height, "Concrete1.png") {

}

bool Road::onCollision(Player& player) {

    return true;
}

// Potal
Potal::Potal(float x, float y, float width, float height, MapManager& mapManager, int nextMap, int nextX, int nextY)
    : Tile(x,y,width,height,"potal.png"),mapManager(mapManager), nextMap(nextMap), nextX(nextX), nextY(nextY)
{

}

bool Potal::onCollision(Player& player) {
    mapManager.changeMap(nextMap, nextX, nextY);
    return false;
}

// MapManager
MapManager::MapManager(Player& player) : playerTile(Tile::tileSize, Tile::tileSize, Tile::tileSize, Tile::tileSize, player) {
    playerX = 1;
    playerY = 1;
    // 맵 생성
    maps.emplace_back(30, 20);
    maps.emplace_back(20, 20);
    {
        Map& map = maps[0];

        // 전체를 grass로 채우기
        for (int i = 0; i < map.width; ++i) {
            for (int j = 0; j < map.height; ++j) {
                map.grid[i][j] = new Grass(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
            }
        }

        // 주어진 범위를 concrete으로 채우기
        for (int i = 1; i <= 5; ++i) {
            for (int j = 1; j <= 3; ++j) {
                delete map.grid[i][j]; // 기존 Grass 타일 객체 삭제
                map.grid[i][j] = new Road(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
            }
        }
        delete map.grid[10][5];
        map.grid[10][5] = new Potal(10 * Tile::tileSize, 5 * Tile::tileSize, Tile::tileSize, Tile::tileSize, *this, 1, 1, 5);
    }

    {
        Map& map = maps[1];

        for (int i = 0; i < map.width; ++i) {
            for (int j = 0; j < map.height; ++j) {
                map.grid[i][j] = new Grass(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
            }
        }    
        delete map.grid[0][5];
        map.grid[0][5] = new Potal(0, 5 * Tile::tileSize, Tile::tileSize, Tile::tileSize, *this, 0, 9, 5);
    }

    changeMap(0, 1, 1);
}

void MapManager::changeMap(int mapNum, int x, int y) {
    currentMap = mapNum;
    playerX = x;
    playerY = y;
    playerTile.move(x * Tile::tileSize, y * Tile::tileSize);
}

void MapManager::movePlayer(int dx, int dy) {
    int nextX = playerX + dx;
    int nextY = playerY + dy;
    if (nextX < 0 || nextX >= maps[currentMap].width || nextY < 0 || nextY >= maps[currentMap].height) return;
    if (maps[currentMap].grid[nextX][nextY]->onCollision(playerTile.getPlayer())) {
        playerTile.move(nextX * Tile::tileSize, nextY * Tile::tileSize);
        playerX = nextX;
        playerY = nextY;
    }
    if (dx * playerTile.getDirection() < 0) {
        playerTile.inverse();
    }
}

void MapManager::draw(RenderWindow& window) {
    maps[currentMap].draw(window);
    playerTile.draw(window);
}