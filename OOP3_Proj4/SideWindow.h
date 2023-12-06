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
	bool isActivate = false;

public:
	SideWindow();
	void draw(sf::RenderWindow& window);
	void updateText(const std::string& newText);
	bool getActivate() { return isActivate; }
	void setActivate(bool value) { isActivate = value; }
};

#endif


