#include<iostream>
#include "InfoWindow.h"
#include <SFML/Graphics.hpp>

#define WIDTH 1600
#define HEIGHT 900

InfoWindow::InfoWindow(Player& player, MapManager& mapManager) {
		
	box.setSize(sf::Vector2f(400, 500));
	box.setFillColor(sf::Color(204, 204, 204));
	setPosition(box, mapManager, 150, 50);

	font.loadFromFile("PKMN RBYGSC.ttf");


	for (int i = 0; i < 8; i++) {
		selection[i].setFont(font);
		selection[i].setCharacterSize(20);
		selection[i].setFillColor(sf::Color::Black);
	}
	selection[0].setString("HP: " + std::to_string(player.curmon().getHp()) + " /" + std::to_string(player.curmon().getMaxHp()));
	selection[1].setString("MP: " + std::to_string(player.curmon().getMp()) + " /" + std::to_string(player.curmon().getMaxMp()));
	selection[2].setString("ATK: " + std::to_string(player.curmon().getAtk()));
	selection[3].setString("DEF: " + std::to_string(player.curmon().getDef()));
	selection[4].setString("CRI: " + std::to_string(player.curmon().getCrit()));
	selection[5].setString("EVD: " + std::to_string(player.curmon().getEvad()));
	selection[6].setString("Lv: " + std::to_string(player.curmon().getLv()));
	selection[7].setString("Exp: " + std::to_string(player.curmon().getExp()) + " /" + std::to_string(player.curmon().getMExp()));

	
	setPosition(selection[0], mapManager, 220, 100);
	setPosition(selection[1], mapManager, 220, 150);
	setPosition(selection[2], mapManager, 220, 200);
	setPosition(selection[3], mapManager, 220, 250);
	setPosition(selection[4], mapManager, 220, 300);
	setPosition(selection[5], mapManager, 220, 350);
	setPosition(selection[6], mapManager, 220, 400);
	setPosition(selection[7], mapManager, 220, 450);

}
InfoWindow::~InfoWindow() {

}

void InfoWindow::draw(sf::RenderWindow& window) {
	window.draw(box);
	for (int i = 0; i < 8; i++) {
		window.draw(selection[i]);
	}
	window.draw(arrow);
}

void InfoWindow::setPosition(sf::Transformable& object, MapManager& mapManager, float x, float y) {
	centerX = mapManager.getPlayerX() * Tile::tileSize;
	centerY = mapManager.getPlayerY() * Tile::tileSize;

	float mapPixelWidth = mapManager.maps[mapManager.getCurrentMap()].width * Tile::tileSize;
	float mapPixelHeight = mapManager.maps[mapManager.getCurrentMap()].height * Tile::tileSize;

	if (centerX - WIDTH/2 < 0) {
		centerX = WIDTH/2;
	}
	if (centerY - HEIGHT/2 < 0) {
		centerY = HEIGHT / 2;
	}
	if (centerX + WIDTH / 2 > mapPixelWidth) {
		centerX = mapPixelWidth - WIDTH / 2;
	}
	if (centerY + HEIGHT / 2 > mapPixelHeight) {
		centerY = mapPixelHeight - HEIGHT / 2;
	}

	object.setPosition(centerX - WIDTH / 2 + x, centerY - HEIGHT / 2 + y);
}

