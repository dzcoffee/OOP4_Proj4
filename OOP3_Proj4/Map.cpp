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
Road::Road(float x, float y, float width, float height) : Tile(x, y, width, height, "Road.png") {

}

bool Road::onCollision(Player& player) {

    return true;
}

// Potal
Potal::Potal(float x, float y, float width, float height, MapManager& mapManager, int nextMap, int nextX, int nextY)
    : Tile(x,y,width,height, "Portal.png"), mapManager(mapManager), nextMap(nextMap), nextX(nextX), nextY(nextY)
{

}

bool Potal::onCollision(Player& player) {
    mapManager.changeMap(nextMap, nextX, nextY);
    return false;
}

Wall::Wall(float x, float y, float width, float height) : Tile(x, y, width, height,"wall_normal1.png") {

}

bool Wall::onCollision(Player& player) {

    return false;
}

Wall2::Wall2(float x, float y, float width, float height) : Tile(x, y, width, height, "wall_tree.png") { //tree_wall

}

bool Wall2::onCollision(Player& player) {

    return false;
}

Wall3::Wall3(float x, float y, float width, float height) : Tile(x, y, width, height, "wall_normal2.png") { //corner_wall

}

bool Wall3::onCollision(Player& player) {

    return false;
}

Wall4::Wall4(float x, float y, float width, float height) : Tile(x, y, width, height, "wall_water.png") { //corner_wall

}

bool Wall4::onCollision(Player& player) {

    return false;
}

Event_Tile::Event_Tile(float x, float y, float width, float height) : Tile(x, y, width, height, "EV.png") { //event TIle

}

bool Event_Tile::onCollision(Player& player) {

    return true;
}

// MapManager
MapManager::MapManager(Player& player) : playerTile(Tile::tileSize, Tile::tileSize, Tile::tileSize, Tile::tileSize, player) {
    
    view = sf::View(sf::FloatRect(0, 0, 1600, 900));

    // 맵 생성
    maps.emplace_back(30, 22);
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
        map.grid[0][4] = new Potal(10 * Tile::tileSize, 5 * Tile::tileSize, Tile::tileSize, Tile::tileSize, *this, 1, 1, 5);
        delete map.grid[0][5];
        map.grid[0][5] = new Potal(10 * Tile::tileSize, 5 * Tile::tileSize, Tile::tileSize, Tile::tileSize, *this, 1, 1, 5);
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

    changeMap(0, 5, 5);
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
    float viewHalfWidth = view.getSize().x / 2;
    float viewHalfHeight = view.getSize().y / 2;

    float newCenterX = nextX * Tile::tileSize;
    float newCenterY = nextY * Tile::tileSize;

    // 맵의 크기에 따라 view의 중심 위치를 제한

    float mapPixelWidth = maps[currentMap].width * Tile::tileSize;
    float mapPixelHeight = maps[currentMap].height * Tile::tileSize;

    if (newCenterX - viewHalfWidth < 0) {
        newCenterX = viewHalfWidth;
    }
    if (newCenterY - viewHalfHeight < 0) {
        newCenterY = viewHalfHeight;
    }
    if (newCenterX + viewHalfWidth > mapPixelWidth) {
        newCenterX = mapPixelWidth - viewHalfWidth;
    }
    if (newCenterY + viewHalfHeight > mapPixelHeight) {
        newCenterY = mapPixelHeight - viewHalfHeight;
    }
    view.setCenter(sf::Vector2f(newCenterX, newCenterY));
}

void MapManager::draw(RenderWindow& window) {
    maps[currentMap].draw(window);
    playerTile.draw(window);
}

sf::View& MapManager::getView() {
    return view; 
}