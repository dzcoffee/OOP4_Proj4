#include<iostream>
#include "Player.h"
#include <SFML/Graphics.hpp>
#include "Map.h"

#ifndef _INFOWINDOW_H_
#define _INFOINDOW_H_

class InfoWindow {
private:
	sf::RectangleShape box;
	sf::Font font;
	sf::ConvexShape arrow; // »≠ªÏ«•

	sf::Text selection[8];

	oopmon* playerMon = nullptr;

	float centerX;
	float centerY;

public:
	InfoWindow(Player& player, MapManager& mapManager);
	~InfoWindow();
	void draw(sf::RenderWindow& window);
	void setPosition(sf::Transformable& object, MapManager& mapManager,float x, float y);

};

#endif

