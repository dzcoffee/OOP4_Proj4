#include <iostream>
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "SideWindow.h"

SideWindow::SideWindow() {
	// 네모 박스 초기화
	box.setSize(sf::Vector2f(1000, 700));
	box.setFillColor(sf::Color::White);
	box.setPosition(300, 100);

	font.loadFromFile("PKMN RBYGSC.ttf");
	text.setFont(font);
	text.setCharacterSize(20); //폰트 크기 수정

	text.setString("Test"); //text String 입력
	text.setPosition(400, 120);
	text.setFillColor(sf::Color::Blue);
	arrow.setPointCount(3);
	arrow.setPoint(0, sf::Vector2f(0, 0));
	arrow.setPoint(1, sf::Vector2f(20, 10));
	arrow.setPoint(2, sf::Vector2f(0, 20));
	arrow.setFillColor(sf::Color::Blue);
	arrow.setPosition(360, 120);

}

void SideWindow::moveArrow() {
	arrow.setPosition(360, 120 + 40 * focused);
}

void SideWindow::focusUp() {
	if (focused > 0) {
		focused--;
		moveArrow();
	}
}

void SideWindow::focusDown() {
	if (focused < 4) {
		focused++;
		moveArrow();
	}
}

void SideWindow::setEnable() {
	isActivate = true;
	focused = 0;
	moveArrow();
}

void SideWindow::setDisable() {
	isActivate = false;
}

void SideWindow::draw(sf::RenderWindow& window) {
	window.draw(box);
	window.draw(text);
	window.draw(arrow);
}

void SideWindow::updateText(const string& newText) {
	text.setString(newText);
}
