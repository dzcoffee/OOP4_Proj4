#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>


#ifndef _SIDEWINDOW_H_
#define _SIDEWINDOW_H_


class SideWindow {
private:
	sf::RectangleShape box;
	sf::ConvexShape arrow;
	sf::Text text; // ±ÛÀÚ
	sf::Font font;
	bool isActivate = false;
	int focused = 0;


	void moveArrow();
public:
	SideWindow();
	void draw(sf::RenderWindow& window);
	void updateText(const std::string& newText);
	bool getActivate() { return isActivate; }
	void setEnable();
	void setDisable();
	int getFocused() { return focused; }
	void focusUp();
	void focusDown();
};

#endif


