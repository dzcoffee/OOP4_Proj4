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
            delete grid[i][j]; // ���� �Ҵ��� Tile ��ü �޸� ����
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
PlayerTile::PlayerTile(float x, float y, float width, float height, Player& player) : Tile(x, y, width, height, "Puang.png"), player(player) {

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
    if (rand() % 8 == 0) {
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

Wall4::Wall4(float x, float y, float width, float height) : Tile(x, y, width, height, "wall_water.png") { //water_wall

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
MapManager::MapManager(Player& player, gamecontroller& controller) : playerTile(Tile::tileSize, Tile::tileSize, Tile::tileSize, Tile::tileSize, player), controller(controller) {

    // �� ����
    maps.emplace_back(30, 22);
    maps.emplace_back(20, 20);
    maps.emplace_back(20, 40);
    maps.emplace_back(20, 20);
    {
        Map& map = maps[0];

        // ��ü�� grass�� ä���
        for (int i = 0; i < map.width; ++i) {
            for (int j = 0; j < map.height; ++j) {
                map.grid[i][j] = new Grass(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize, controller);
            }
        }

        // �־��� ������ concrete���� ä���
        for (int i = 0; i <= 29; ++i) {
            for (int j = 0; j <= 1; ++j) {
                delete map.grid[i][j]; // ���� Grass Ÿ�� ��ü ����
                map.grid[i][j] = new Wall(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
            }
        }

        for (int i = 28; i <= 29; ++i) {
            for (int j = 2; j <= 19; ++j) {
                delete map.grid[i][j]; // ���� Grass Ÿ�� ��ü ����
                map.grid[i][j] = new Wall(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
            }
        }

        for (int i = 0; i <= 29; ++i) {
            for (int j = 20; j <= 21; ++j) {
                delete map.grid[i][j]; // ���� Grass Ÿ�� ��ü ����
                map.grid[i][j] = new Wall(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
            }
        }

        for (int i = 0; i <= 1; ++i) {
            for (int j = 8; j <= 19; ++j) {
                delete map.grid[i][j]; // ���� Grass Ÿ�� ��ü ����
                map.grid[i][j] = new Wall(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
            }
        }


        for (int i = 2; i <= 11; ++i) {
            int j = 8;
            delete map.grid[i][j]; // ���� Grass Ÿ�� ��ü ����
            map.grid[i][j] = new Wall(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
        }

        for (int j = 2; j <= 14; ++j) {
            int i = 15;
            delete map.grid[i][j]; // ���� Grass Ÿ�� ��ü ����
            map.grid[i][j] = new Wall(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
        }

        for (int i = 2; i <= 14; ++i) {
            if (i == 9 || i == 10) {
                continue;
            }
            int j = 14;
            delete map.grid[i][j]; // ���� Grass Ÿ�� ��ü ����
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

        for (int i = 0; i <= 29; ++i) {
            for (int j = 0; j <= 1; ++j) {
                if (i == 17 || i == 18) {
                    if (j == 1) {
                        delete map.grid[i][j];
                        map.grid[i][j] = new Road(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
                    }
                    continue;
                }
                delete map.grid[i][j];
                map.grid[i][j] = new Wall2(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
            }
        }

        for (int i = 28; i <= 29; ++i) {
            for (int j = 2; j <= 29; ++j) {
                if (j == 4 || j == 5) {
                    if (i == 28) {
                        delete map.grid[i][j];
                        map.grid[i][j] = new Road(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
                    }
                    continue;
                }
                delete map.grid[i][j];
                map.grid[i][j] = new Wall2(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
            }
        }

        for (int i = 0; i <= 27; ++i) {
            for (int j = 28; j <= 29; ++j) {
                delete map.grid[i][j];
                map.grid[i][j] = new Wall2(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
            }
        }

        for (int i = 0; i <= 1; ++i) {
            for (int j = 2; j <= 27; ++j) {
                delete map.grid[i][j];
                map.grid[i][j] = new Wall2(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
            }
        }

        for (int j = 2; j <= 24; ++j) {
            int i = 22;
            delete map.grid[i][j];
            map.grid[i][j] = new Wall(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
        }

        for (int i = 6; i <= 21; ++i) {
            int j = 24;
            delete map.grid[i][j];
            map.grid[i][j] = new Wall(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
        }

        for (int j = 6; j <= 24; ++j) {
            int i = 6;
            delete map.grid[i][j];
            map.grid[i][j] = new Wall(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
        }

        for (int j = 2; j <= 19; ++j) {
            int i = 13;
            delete map.grid[i][j];
            map.grid[i][j] = new Wall(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
        }

        for (int i = 14; i <= 21; ++i) {
            for (int j = 2; j <= 19; ++j) {
                if (i == 17 || i == 18) {
                    delete map.grid[i][j];
                    map.grid[i][j] = new Road(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
                    continue;
                }
                delete map.grid[i][j];
                map.grid[i][j] = new Wall4(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
            }
        }

        delete map.grid[29][4]; // move to map1
        map.grid[29][4] = new Potal(29 * Tile::tileSize, 4 * Tile::tileSize, Tile::tileSize, Tile::tileSize, *this, 0, 1, 4);
        delete map.grid[29][5];
        map.grid[29][5] = new Potal(29 * Tile::tileSize, 5 * Tile::tileSize, Tile::tileSize, Tile::tileSize, *this, 0, 1, 5);

        delete map.grid[17][0]; // move to map3
        map.grid[17][0] = new Potal(17 * Tile::tileSize, 0 * Tile::tileSize, Tile::tileSize, Tile::tileSize, *this, 2, 9, 38); 
        delete map.grid[18][0];
        map.grid[18][0] = new Potal(18 * Tile::tileSize, 0 * Tile::tileSize, Tile::tileSize, Tile::tileSize, *this, 2, 10, 38);
    }

    {
        Map& map = maps[2];

        for (int i = 0; i < map.width; ++i) {
            for (int j = 0; j < map.height; ++j) {
                map.grid[i][j] = new Road(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
            }

        }


        for (int i = 5; i <= 14; ++i) { //island 0
            for (int j = 35; j <= 39; ++j) {
                delete map.grid[i][j];
                map.grid[i][j] = new Road(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
            }
        }

        for (int i = 15; i <= 18; ++i) { //island 1
            for (int j = 26; j <= 30; ++j) {
                delete map.grid[i][j];
                map.grid[i][j] = new Grass(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize, controller);
            }
        }

        for (int i = 1; i <= 6; ++i) { //island 2
            for (int j = 16; j <= 20; ++j) {
                delete map.grid[i][j];
                map.grid[i][j] = new Grass(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize, controller);
            }
        }

        for (int i = 12; i <= 18; ++i) { //island 3
            for (int j = 7; j <= 11; ++j) {
                delete map.grid[i][j];
                map.grid[i][j] = new Grass(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize, controller);
            }
        }

        for (int i = 1; i <= 6; ++i) { //island 4
            for (int j = 1; j <= 5; ++j) {
                delete map.grid[i][j];
                map.grid[i][j] = new Road(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize);
            }
        }

        delete map.grid[9][35]; // move to map3 island0 -> island1
        map.grid[9][35] = new Potal(10 * Tile::tileSize, 5 * Tile::tileSize, Tile::tileSize, Tile::tileSize, *this, 2, 16, 29);
        delete map.grid[16][30]; // move to map3 island1 -> island0
        map.grid[16][30] = new Potal(10 * Tile::tileSize, 5 * Tile::tileSize, Tile::tileSize, Tile::tileSize, *this, 2, 9, 36);

        delete map.grid[15][27]; // move to map3 island1 -> -island2
        map.grid[15][27] = new Potal(10 * Tile::tileSize, 5 * Tile::tileSize, Tile::tileSize, Tile::tileSize, *this, 2, 5, 18);
        delete map.grid[6][18]; // move to map2 island2 -> island1
        map.grid[6][18] = new Potal(10 * Tile::tileSize, 5 * Tile::tileSize, Tile::tileSize, Tile::tileSize, *this, 2, 16, 27);

        delete map.grid[2][16]; // move to map3 island2 -> island3
        map.grid[2][16] = new Potal(10 * Tile::tileSize, 5 * Tile::tileSize, Tile::tileSize, Tile::tileSize, *this, 2, 15, 10);
        delete map.grid[15][11]; // move to map3 island3 -> island2
        map.grid[15][11] = new Potal(10 * Tile::tileSize, 5 * Tile::tileSize, Tile::tileSize, Tile::tileSize, *this, 2, 2, 17);

        delete map.grid[12][9]; // move to map3 island3 -> island4
        map.grid[12][9] = new Potal(10 * Tile::tileSize, 5 * Tile::tileSize, Tile::tileSize, Tile::tileSize, *this, 2, 5, 3);
        delete map.grid[6][3]; // move to map3 island4 -> island3
        map.grid[6][3] = new Potal(10 * Tile::tileSize, 5 * Tile::tileSize, Tile::tileSize, Tile::tileSize, *this, 2, 13, 9);



        delete map.grid[9][39]; // move to map2
        map.grid[9][39] = new Potal(10 * Tile::tileSize, 5 * Tile::tileSize, Tile::tileSize, Tile::tileSize, *this, 1, 17, 1);
        delete map.grid[10][39];
        map.grid[10][39] = new Potal(10 * Tile::tileSize, 5 * Tile::tileSize, Tile::tileSize, Tile::tileSize, *this, 1, 18, 1);

        delete map.grid[0][3]; // move to map4
        map.grid[0][4] = new Potal(10 * Tile::tileSize, 5 * Tile::tileSize, Tile::tileSize, Tile::tileSize, *this, 3, 1, 4);
        delete map.grid[0][4];
        map.grid[0][5] = new Potal(10 * Tile::tileSize, 5 * Tile::tileSize, Tile::tileSize, Tile::tileSize, *this, 3, 1, 5);
    }

    {
        Map& map = maps[3];

        for (int i = 0; i < map.width; ++i) {
            for (int j = 0; j < map.height; ++j) {
                map.grid[i][j] = new Grass(i * Tile::tileSize, j * Tile::tileSize, Tile::tileSize, Tile::tileSize, controller);
            }
        }

        delete map.grid[19][9]; // move to map3
        map.grid[19][9] = new Potal(10 * Tile::tileSize, 5 * Tile::tileSize, Tile::tileSize, Tile::tileSize, *this, 2, 1, 4);
        delete map.grid[19][10];
        map.grid[19][10] = new Potal(10 * Tile::tileSize, 5 * Tile::tileSize, Tile::tileSize, Tile::tileSize, *this, 2, 1, 5);
    }

    changeMap(0, 22, 5);

}

void MapManager::changeMap(int mapNum, int x, int y) {
    currentMap = mapNum;
    playerX = x;
    playerY = y;
    playerTile.move(x * Tile::tileSize, y * Tile::tileSize);
    playerTile.getPlayer().setMapLv(mapNum + 1);
    updateView(x, y);
}

void MapManager::movePlayer(int dx, int dy) {
    int nextX = playerX + dx;
    int nextY = playerY + dy;
    if (nextX < 0 || nextX >= maps[currentMap].width || nextY < 0 || nextY >= maps[currentMap].height) return;
    if (maps[currentMap].grid[nextX][nextY]->canPass()) {
        playerTile.move(nextX * Tile::tileSize, nextY * Tile::tileSize);
        playerX = nextX;
        playerY = nextY;
        updateView(nextX, nextY);
        maps[currentMap].grid[nextX][nextY]->onCollision(playerTile.getPlayer());
        /*if (maps[currentMap].grid[nextX][nextY]->onCollision(playerTile.getPlayer())) {
        }*/
    }
    if (dx * playerTile.getDirection() < 0) {
        playerTile.inverse();
    }
}

void MapManager::updateView(int x, int y) {

    float viewHalfWidth = view.getSize().x / 2;
    float viewHalfHeight = view.getSize().y / 2;

    float newCenterX = x * Tile::tileSize;
    float newCenterY = y * Tile::tileSize;

    // ���� ũ�⿡ ���� view�� �߽� ��ġ�� ����

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
    controller.setCenter(newCenterX, newCenterY);
}

void MapManager::draw(RenderWindow& window) {
    window.setView(view);
    maps[currentMap].draw(window);
    playerTile.draw(window);
}

void MapManager::onPlayerDied() {
    playerTile.getPlayer().curmon().resurrection();
    changeMap(0, 5, 5);
}