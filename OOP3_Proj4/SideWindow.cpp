
#include<iostream>
#include "Player.h"
#include <SFML/Graphics.hpp>

SideWindow::SideWindow() {
	// 네모 박스 초기화
	box.setSize(sf::Vector2f(300, 700));
	box.setFillColor(sf::Color::White);
	box.setPosition(100, 100);

	font.loadFromFile("PKMN RBYGSC.ttf");

	text.setFont(font);
	text.setCharacterSize(20); //폰트 크기 수정
	text.setString("Example Text"); //text String 입력
	text.setPosition(150, 120);
	text.setFillColor(sf::Color::Blue);

	// 화살표 초기화 (삼각형)
	arrow.setPointCount(3);
	arrow.setPoint(0, sf::Vector2f(0, 0));
	arrow.setPoint(1, sf::Vector2f(20, 10));
	arrow.setPoint(2, sf::Vector2f(0, 20));
	arrow.setFillColor(sf::Color::Black);
	arrow.setPosition(120, 120);
}

void SideWindow::draw(sf::RenderWindow& window) {
	window.draw(box);
	window.draw(text);
	window.draw(arrow);
}
/*
void SideWindow::updateText(const string& newText) {
	text.setString(newText);
}

void SideWindow::display() {
	this->display();
}
*/