#ifndef _SIDEWINDOW_H_
#define _SIDEWINDOW_H_

#include <iostream>
#include "player.cpp"
#include <SFML/Graphics.hpp>
#include <string.h>

class SideWindow {
private:
	sf::RectangleShape box;
	sf::Text text; // ±ÛÀÚ
	sf::Font font;

public:
	SideWindow();
	void draw(sf::RenderWindow& window);
	void updateText(const string& newText);
	void display();
};

#endif


