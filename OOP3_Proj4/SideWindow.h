#ifndef _SIDEWINDOW_H_
#define _SIDEWINDOW_H_

#include <iostream>
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <string>

class SideWindow {
private:
	sf::RectangleShape box;
	sf::Text text; // 글자
	sf::Font font;
	sf::ConvexShape arrow; // 화살표

public:
	SideWindow();
	void draw(sf::RenderWindow& window);
	void updateText(const string& newText);
	void display();
};

#endif