#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Gamecontroller.h"

#ifndef _MAP_H_
#define _MAP_H_

using namespace std;
using namespace sf;

class MapManager;


class Tile {
protected:
	RectangleShape shape;
	Texture texture;
	bool _canPass;
public:
	Tile(float x, float y, float width, float height, const std::string& textureFile, bool canPass = true);
	static const int tileSize = 100; // Ÿ���� ũ�⸦ ��Ÿ���� ���� ��� ���� �߰�
	virtual ~Tile() = default;
	void draw(sf::RenderWindow& window);
	bool canPass();
	virtual bool onCollision(Player& player) = 0;		// �浹 �� �̺�Ʈ
};

class PlayerTile : public Tile {
private:
	Player& player;
	int direction = -1;
public:
	PlayerTile(float x, float y, float width, float height, Player& player);
	virtual bool onCollision(Player& player);
	void move(float x, float y);
	Player& getPlayer();
	int getDirection();
	void inverse();
};

class Grass : public Tile {
private:
	gamecontroller& controller;
public:
	Grass(float x, float y, float width, float height, gamecontroller& controller);
	virtual bool onCollision(Player& player);
};

class Road : public Tile {
public:
	Road(float x, float y, float width, float height);
	virtual bool onCollision(Player& player);
};

class Potal : public Tile {
private:
	int nextMap;
	int nextX;
	int nextY;
	MapManager& mapManager;
public:
	Potal(float x, float y, float width, float height, MapManager& manager, int nextMap, int nextX, int nextY);
	virtual bool onCollision(Player& player);
};

class Wall : public Tile {
public:
	Wall(float x, float y, float width, float height);
	virtual bool onCollision(Player& player);
};


class Map {
public:
	static const int VISIBLE_WIDTH = 32;
	static const int VISIBLE_HEIGHT = 18;

	int width;
	int height;

	vector<vector<Tile*>> grid;

	Map(int width, int height);
	~Map();
	void draw(RenderWindow& window);
};

// �� ����
class MapManager {
private:
	vector<Map> maps;
	int currentMap = 0;
	PlayerTile playerTile;
	int playerX;
	int playerY;

public:
	MapManager(Player& player, gamecontroller& cotroller);
	void changeMap(int mapNum, int x, int y);
	void movePlayer(int dx, int dy);
	void draw(RenderWindow& window);
};

#endif