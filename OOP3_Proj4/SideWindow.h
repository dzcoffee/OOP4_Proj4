#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#ifndef _SIDEWINDOW_H_
#define _SIDEWINDOW_H_


class SideWindow {
private:
	sf::RectangleShape box;
	sf::Text text; // ±ÛÀÚ
	sf::Font font;

public:
	SideWindow();
	void draw(sf::RenderWindow& window);
	void updateText(const std::string& newText);
};

#endif


