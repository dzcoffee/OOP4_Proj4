#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "Oopmon.h"

#ifndef _SIDEWINDOW_H_
#define _SIDEWINDOW_H_

class ProgressBar{
private:
	sf::RectangleShape back;
	sf::RectangleShape fore;
public:
	ProgressBar();
	void draw(sf::RenderWindow& window);
	void update(int currentHP, int maxHP);
	void setPosition(float x, float y);
	void setColor(sf::Color);
};

class SideWindow {
private:
	sf::RectangleShape box;
	sf::ConvexShape arrow;

	sf::RectangleShape player;
	sf::Texture playerTexture;
	sf::RectangleShape enemy;
	sf::Texture enemyTexture;
	ProgressBar playerHP;
	ProgressBar playerMP;
	ProgressBar enemyHP;
	ProgressBar enemyMP;

	sf::Text state;
	sf::Text selection[6];
	sf::Font font;
	bool isActivate = false;
	int focused = 0;
	float centerX;
	float centerY;

	oopmon* playerMon = nullptr;
	oopmon* enemyMon = nullptr;

	void moveArrow();
	void setPosition(sf::Transformable& object, float x, float y);
	void setPosition(ProgressBar& hp, float x, float y);
public:
	SideWindow();
	void draw(sf::RenderWindow& window);
	void updateText(const std::string& newText);
	void appendText(const std::string& append);
	bool getActivate() { return isActivate; }
	void setEnable(oopmon* playerMon, oopmon* enemyMon);
	void setDisable();
	void update();
	int getFocused() { return focused + 1; }
	void focusUp();
	void focusDown();
	void focusLeft();
	void focusRight();
	void setCenter(float x, float y);
};

#endif


