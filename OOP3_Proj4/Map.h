#ifndef _MAP_H_
#define _MAP_H_

#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

class Tile {
protected:
	RectangleShape shape;
	Texture texture;
public:
	Tile(float x, float y, float width, float height, const std::string& textureFile);
	static const int tileSize = 100; // Ÿ���� ũ�⸦ ��Ÿ���� ���� ��� ���� �߰�
	virtual ~Tile() = default;
	void draw(sf::RenderWindow& window);
};

class Grass : public Tile {
public:
	Grass(float x, float y, float width, float height);
};

class Road : public Tile {
public:
	Road(float x, float y, float width, float height);
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
#endif