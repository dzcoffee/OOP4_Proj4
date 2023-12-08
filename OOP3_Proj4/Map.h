#ifndef _MAP_H_
#define _MAP_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include "player.cpp"

using namespace std;
using namespace sf;

class MapManager;

class Tile {
protected:
	RectangleShape shape;
	Texture texture;
public:
	Tile(float x, float y, float width, float height, const std::string& textureFile);
	static const int tileSize = 100; // 타일의 크기를 나타내는 정적 멤버 변수 추가
	virtual ~Tile() = default;
	void draw(sf::RenderWindow& window);
	virtual bool onCollision(Player& player) = 0;		// 충돌 시 이벤트
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
public:
	Grass(float x, float y, float width, float height);
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

class Wall2 : public Tile {
public:
	Wall2(float x, float y, float width, float height);
	virtual bool onCollision(Player& player);
};

class Wall3 : public Tile {
public:
	Wall3(float x, float y, float width, float height);
	virtual bool onCollision(Player& player);
};

class Wall4 : public Tile {
public:
	Wall4(float x, float y, float width, float height);
	virtual bool onCollision(Player& player);
};

class Event_Tile : public Tile {
public:
	Event_Tile(float x, float y, float width, float height);
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

// 맵 관리
class MapManager {
private:
	vector<Map> maps;
	int currentMap = 0;
	PlayerTile playerTile;
	int playerX;
	int playerY;
	View view;

public:
	MapManager(Player& player);
	void changeMap(int mapNum, int x, int y);
	void movePlayer(int dx, int dy);
	void draw(RenderWindow& window);
	void moveView(int mapNum, int x, int y);
	View& getView();
};

#endif