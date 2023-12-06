#include <iostream>
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "SideWindow.h"

SideWindow::SideWindow() {
	// 네모 박스 초기화
	box.setSize(sf::Vector2f(300, 700));
	box.setFillColor(sf::Color::White);
	box.setPosition(100, 100);

	font.loadFromFile("PKMN RBYGSC.ttf");
	text.setFont(font);
	text.setCharacterSize(20); //폰트 크기 수정

	text.setString("Test"); //text String 입력
	text.setPosition(150, 120);
	text.setFillColor(sf::Color::Blue);
}

void SideWindow::draw(sf::RenderWindow& window) {
	window.draw(box);
	window.draw(text);
}

void SideWindow::updateText(const string& newText) {
	text.setString(newText);
}
