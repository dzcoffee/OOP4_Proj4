#include "Map.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

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
Tile::Tile(float x, float y, float width, float height, const std::string& textureFile, bool canPass) {
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, height));
    if (!texture.loadFromFile(textureFile)) {
        std::cout << "Failed to load texture from " << textureFile << std::endl;
    }
    shape.setTexture(&texture);
    this->_canPass = canPass;
}

void Tile::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

bool Tile::canPass() {
    return _canPass;
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
Grass::Grass(float x, float y, float width, float height, gamecontroller& controller) : Tile(x, y, width, height, "grass1.png"), controller(controller) {

}

bool Grass::onCollision(Player& player) {
    srand((unsigned int)time(NULL));
    if (rand() % 4 == 0) {
        controller.battle();
    }
    return true;
}

// Road
Road::Road(float x, float y, float width, float height) : Tile(x, y, width, height, "Road.png") {

}

bool Road::onCollision(Player& player) {

    return true;
}

// Potal
Potal::Potal(float x, float y, float width, float height, MapManager& mapManager, int nextMap, int nextX, int nextY)
    : Tile(x, y, width, height, "Portal.png"), mapManager(mapManager), nextMap(nextMap), nextX(nextX), nextY(nextY)
{

}

bool Potal::onCollision(Player& player) {
    mapManager.changeMap(nextMap, nextX, nextY);
    return false;
}

Wall::Wall(float x, float y, float width, float height) : Tile(x, y, width, height, "wall_normal1.png", false) {

}

bool Wall::onCollision(Player& player) {

    return false;
}

// MapManager
MapManager::MapManager(Player& player, gamecontroller& controller) : playerTile(Tile::tileSize, Tile::tileSize, Tile::tileSize, Tile::tileSize, player) {

    // 맵 생성
    maps.emplace_back(30, 22);
    maps.emplace_back(20, 20);
    {
        Map& map = maps[0];

        // 전체를 grass로 채우기
        for (int i = 0; i < map.width; ++i) {
            for (int j = 0; j < map.height; ++j) {
                map.grid[i][j] = new Grass(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize, controller);
            }
        }

        // 주어진 범위를 concrete으로 채우기
        for (int i = 0; i <= 29; ++i) {
            for (int j = 0; j <= 1; ++j) {
                delete map.grid[i][j]; // 기존 Grass 타일 객체 삭제
                map.grid[i][j] = new Wall(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
            }
        }

        for (int i = 28; i <= 29; ++i) {
            for (int j = 2; j <= 19; ++j) {
                delete map.grid[i][j]; // 기존 Grass 타일 객체 삭제
                map.grid[i][j] = new Wall(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
            }
        }

        for (int i = 0; i <= 29; ++i) {
            for (int j = 20; j <= 21; ++j) {
                delete map.grid[i][j]; // 기존 Grass 타일 객체 삭제
                map.grid[i][j] = new Wall(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
            }
        }

        for (int i = 0; i <= 1; ++i) {
            for (int j = 8; j <= 19; ++j) {
                delete map.grid[i][j]; // 기존 Grass 타일 객체 삭제
                map.grid[i][j] = new Wall(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
            }
        }


        for (int i = 2; i <= 11; ++i) {
            int j = 8;
            delete map.grid[i][j]; // 기존 Grass 타일 객체 삭제
            map.grid[i][j] = new Wall(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
        }

        for (int j = 2; j <= 14; ++j) {
            int i = 15;
            delete map.grid[i][j]; // 기존 Grass 타일 객체 삭제
            map.grid[i][j] = new Wall(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
        }

        for (int i = 2; i <= 14; ++i) {
            if (i == 9 || i == 10) {
                continue;
            }
            int j = 14;
            delete map.grid[i][j]; // 기존 Grass 타일 객체 삭제
            map.grid[i][j] = new Wall(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
        }


        delete map.grid[0][4];
        map.grid[0][4] = new Potal(0 * Tile::tileSize, 4 * Tile::tileSize, Tile::tileSize, Tile::tileSize, *this, 1, 0, 5);
        delete map.grid[0][5];
        map.grid[0][5] = new Potal(0 * Tile::tileSize, 5 * Tile::tileSize, Tile::tileSize, Tile::tileSize, *this, 1, 0, 5);
    }

    {
        Map& map = maps[1];

        for (int i = 0; i < map.width; ++i) {
            for (int j = 0; j < map.height; ++j) {
                map.grid[i][j] = new Grass(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize, controller);
            }
        }
        delete map.grid[0][5];
        map.grid[0][5] = new Potal(0, 5 * Tile::tileSize, Tile::tileSize, Tile::tileSize, *this, 0, 0, 4);
    }

    changeMap(0, 5, 5);
}

void MapManager::changeMap(int mapNum, int x, int y) {
    currentMap = mapNum;
    playerX = x;
    playerY = y;
    playerTile.move(x * Tile::tileSize, y * Tile::tileSize);
    playerTile.getPlayer().setMapLv(mapNum);
}

void MapManager::movePlayer(int dx, int dy) {
    int nextX = playerX + dx;
    int nextY = playerY + dy;
    if (nextX < 0 || nextX >= maps[currentMap].width || nextY < 0 || nextY >= maps[currentMap].height) return;
    if (maps[currentMap].grid[nextX][nextY]->canPass()) {
        playerTile.move(nextX * Tile::tileSize, nextY * Tile::tileSize);
        playerX = nextX;
        playerY = nextY;
        maps[currentMap].grid[nextX][nextY]->onCollision(playerTile.getPlayer());
        /*if (maps[currentMap].grid[nextX][nextY]->onCollision(playerTile.getPlayer())) {
        }*/
    }
    if (dx * playerTile.getDirection() < 0) {
        playerTile.inverse();
    }
}

void MapManager::draw(RenderWindow& window) {
    maps[currentMap].draw(window);
    playerTile.draw(window);
}