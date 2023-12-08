#include <iostream>
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "SideWindow.h"
#define WIDTH 1600
#define HEIGHT 900


SideWindow::SideWindow() {
	// 네모 박스 초기화
	box.setSize(sf::Vector2f(1500, 800));
	box.setFillColor(sf::Color(182,240,182));
	box.setPosition(50, 50);

	font.loadFromFile("PKMN RBYGSC.ttf");

	player.setSize(sf::Vector2f(250, 250));
	player.setFillColor(sf::Color::White);
	player.setPosition(350, 100);

	enemy.setSize(sf::Vector2f(250, 250));
	enemy.setFillColor(sf::Color::White);
	enemy.setPosition(1000, 100);

	state.setFont(font);
	state.setCharacterSize(30);
	updateText("Battle!");
	state.setFillColor(sf::Color::Black);
	state.setPosition(350, 400);
	state.setLineSpacing(1.2);
	
	for (int i = 0; i < 6; i++) {
		selection[i].setFont(font);
		selection[i].setCharacterSize(30);
		selection[i].setFillColor(sf::Color::Black);
	}
	selection[0].setString("1. Tackle");
	selection[1].setString("2. Light Attack");
	selection[2].setString("3. Heavy Attack");
	selection[3].setString("4. Critical up");
	selection[4].setString("5. Evade up");
	selection[5].setString("6. Item");

	arrow.setPointCount(3);
	arrow.setPoint(0, sf::Vector2f(0, 0));
	arrow.setPoint(1, sf::Vector2f(30, 15));
	arrow.setPoint(2, sf::Vector2f(0, 30));
	arrow.setFillColor(sf::Color::Black);
	arrow.setPosition(360, 120);

	playerHP.setColor(sf::Color::Red);
	playerMP.setColor(sf::Color::Blue);
	enemyMP.setColor(sf::Color::Red);
	enemyMP.setColor(sf::Color::Blue);
}

void SideWindow::setPosition(sf::Transformable& object, float x, float y) {
	object.setPosition(centerX - WIDTH / 2 + x, centerY - HEIGHT / 2 + y); 
}

void SideWindow::setPosition(ProgressBar& hp, float x, float y) {
	hp.setPosition(centerX - WIDTH / 2 + x, centerY - HEIGHT / 2 + y);
}

void SideWindow::moveArrow() {
	arrow.setPosition(360, 120 + 40 * focused);
	auto pos = selection[focused].getPosition();
	arrow.setPosition(pos.x - 40, pos.y);
}

void SideWindow::focusUp() {
	if (focused > 1) {
		focused -= 2;
		moveArrow();
	}
}

void SideWindow::focusDown() {
	if (focused < 4) {
		focused += 2;
		moveArrow();
	}
}

void SideWindow::focusLeft() {
	if (focused % 2 != 0) {
		focused--;
		moveArrow();
	}
}

void SideWindow::focusRight() {
	if (focused % 2 == 0) {
		focused++;
		moveArrow();
	}
}

void SideWindow::setEnable(oopmon* playerMon, oopmon* enemyMon) {
	isActivate = true;
	focused = 0;
	this->playerMon = playerMon;
	this->enemyMon = enemyMon;
	setPosition(box, 50, 50);
	setPosition(player, 350, 100);
	setPosition(playerHP, 400, 380);
	setPosition(playerMP, 400, 395);
	setPosition(enemy, 1000, 100);
	setPosition(enemyHP, 1050, 380);
	setPosition(enemyMP, 1050, 395);
	setPosition(state, 350, 420);
	setPosition(selection[0], 200, 650);
	setPosition(selection[1], 1000, 650);
	setPosition(selection[2], 200, 700);
	setPosition(selection[3], 1000, 700);
	setPosition(selection[4], 200, 750);
	setPosition(selection[5], 1000, 750);
	if (!playerTexture.loadFromFile(playerMon->getName()+".png")) {
		std::cout << "Failed to load texture from " << playerMon->getName() + ".png" << std::endl;
	}
	player.setTexture(&playerTexture);
	if (!enemyTexture.loadFromFile(enemyMon->getName() + ".png")) {
		std::cout << "Failed to load texture from " << enemyMon->getName() + ".png" << std::endl;
	}
	enemy.setTexture(&enemyTexture);
	player.setFillColor(sf::Color::White);
	enemy.setFillColor(sf::Color::White);

	update();
	moveArrow();
}

void SideWindow::setDisable() {
	isActivate = false;
}

void SideWindow::update() {
	playerHP.update(playerMon->getHp(), playerMon->getMaxHp());
	playerMP.update(playerMon->getMp(), playerMon->getMaxMp());
	enemyHP.update(enemyMon->getHp(), enemyMon->getMaxHp());
	enemyMP.update(enemyMon->getMp(), enemyMon->getMaxMp());
	if (playerMon->getHp() <= 0) {
		player.setFillColor(sf::Color(124, 124, 124));
	}
	if (enemyMon->getHp() <= 0) {
		enemy.setFillColor(sf::Color(124, 124, 124));
	}
}

void SideWindow::draw(sf::RenderWindow& window) {
	window.draw(box);
	window.draw(player);
	playerHP.draw(window);
	playerMP.draw(window);
	window.draw(enemy);
	enemyHP.draw(window);
	enemyMP.draw(window);
	window.draw(state);
	for (int i = 0; i < 6; i++) {
		window.draw(selection[i]);
	}
	window.draw(arrow);
}

void SideWindow::updateText(const string& newText) {
	state.setString(newText);
	auto rec = state.getGlobalBounds();
	float length = rec.width;
	setPosition(state, (WIDTH - length) / 2, 450);
}

void SideWindow::appendText(const string& append) {
	state.setLineSpacing(1.2);
	state.setString(state.getString() + append);
	auto rec = state.getGlobalBounds();
	float length = rec.width;
	setPosition(state, (WIDTH - length) / 2, 450);
}

void SideWindow::setCenter(float x, float y) {
	centerX = x;
	centerY = y;
}


ProgressBar::ProgressBar() {
	back.setSize(sf::Vector2f(150, 10));
	back.setFillColor(sf::Color(90, 90, 90));
	fore.setSize(sf::Vector2f(150, 10));
	fore.setFillColor(sf::Color::Red);
}

void ProgressBar::draw(sf::RenderWindow& window) {
	window.draw(back);
	window.draw(fore);
}

void ProgressBar::update(int current, int max) {
	if (current <= 0) {
		fore.setSize(sf::Vector2f(0, 10));
	}
	else {
		float ratio = (float)current / max;
		fore.setSize(sf::Vector2f(150 * ratio, 10));
	}
}

void ProgressBar::setPosition(float x, float y) {
	fore.setPosition(x, y);
	back.setPosition(x, y);
}

void ProgressBar::setColor(sf::Color color) {
	fore.setFillColor(color);
}