
#include<iostream>
#include "Player.h"
#include <SFML/Graphics.hpp>

SideWindow::SideWindow() {
	// �׸� �ڽ� �ʱ�ȭ
	box.setSize(sf::Vector2f(300, 700));
	box.setFillColor(sf::Color::White);
	box.setPosition(100, 100);

	font.loadFromFile("PKMN RBYGSC.ttf");

	text.setFont(font);
	text.setCharacterSize(20); //��Ʈ ũ�� ����
	text.setString("Example Text"); //text String �Է�
	text.setPosition(150, 120);
	text.setFillColor(sf::Color::Blue);


}

void SideWindow::draw(sf::RenderWindow& window) {
	window.draw(box);
	window.draw(text);
	window.draw(arrow);
}

void SideWindow::updateText(const string& newText) {
	text.setString(newText);
}

void SideWindow::display() {
	this->display();
}
