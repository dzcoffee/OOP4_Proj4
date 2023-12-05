#include "Player.h"
#include <iostream>
#include <string>
#include <vector>

Player::Player(string name, string monName, montype monType) {
	this->name = name;

	oopmon firstMon(monName, monType, 1);
	this->monList.push_back(firstMon);  // ù��° ���͸� ����Ʈ�� �߰�

	curMonIndex = 0;
	curr_maplv = 1;
}

Player::Player(const Player& other) { // ���� ������
	this->name = other.name;
	this->monList = vector<oopmon>(other.monList);
	this->curMonIndex = other.curMonIndex;
	this->curr_maplv = other.curr_maplv;
}

void Player::displayPlayerInfo() { // �÷��̾� ���� ���

	string message = "Player Name: " + name + "\n";
	displayMonList();
}

void Player::addMonToMonList(oopmon newMon) { // ����Ʈ�� ���� �߰�
	if (monList.size() < 6) {
		monList.push_back(newMon);
		string message = "[" + newMon.getName() + "]" + " added to your oopmon list!";
		gc->getSideWindow()->updateText(message);
		gc->getSideWindow()->draw(mainwindow);
		gc->getSideWindow()->display();
	}
	else {
		gc->getSideWindow()->updateText("The list is full. Cannot add more oopmon.");
		gc->getSideWindow()->draw(mainwindow);
		gc->getSideWindow()->display();
	}
}

void Player::displayMonList() { // ���� ����Ʈ ���
	string message = "Oopmon List: \n";

	if (monList.empty()) {
		message = "List is empty.";
		gc->getSideWindow()->updateText(message);
		gc->getSideWindow()->draw(mainwindow);
		gc->getSideWindow()->display();
	}
	else {
		for (int i = 0; i < monList.size(); i++) {
			message += to_string(i + 1) + " [" + monList[i].getName() + "]"	// 1 [OOPMON]
					+ " Lv. " + to_string(monList[i].getLv()) + " |"		// Lv. 1 |
					+ " HP: " + to_string(monList[i].getHp()) + " |"		// HP: 100 |
					+ " MP: " + to_string(monList[i].getMp());				// MP: 100
			gc->getSideWindow()->updateText(message);
			gc->getSideWindow()->draw(mainwindow);
			gc->getSideWindow()->display();
		}
	}
}

void Player::selectCurMon() { // �÷��̾ ����� ���� ����
	displayMonList();

	sf::Event event;
	switch (event.key.code) {
	case sf::Keyboard::Num1:
		curMonIndex = 0;
		break;
	case sf::Keyboard::Num2:
		curMonIndex = 1;
		break;
	case sf::Keyboard::Num3:
		curMonIndex = 2;
		break;
	case sf::Keyboard::Num4:
		curMonIndex = 3;
		break;
	case sf::Keyboard::Num5:
		curMonIndex = 4;
		break;
	case sf::Keyboard::Num6:
		curMonIndex = 5;
		break;
	}
}

oopmon& Player::curmon() { // �÷��̾ ������ ���͸� ����
	if (curMonIndex >= 0 && curMonIndex < monList.size())
		return monList[curMonIndex];
}