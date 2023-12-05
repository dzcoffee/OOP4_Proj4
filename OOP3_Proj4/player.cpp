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
	this->inventory = vector<string>(other.inventory);
	this->monList = vector<oopmon>(other.monList);
	this->curMonIndex = other.curMonIndex;
	this->curr_maplv = other.curr_maplv;
}

void Player::displayPlayerInfo() { // �÷��̾� ���� ���
	cout << "Player Name: " << name << endl;
	cout << "Oopmon List: " << endl;
	displayMonList();
	cout << "Inventory: ";
	displayInventory();
}

void Player::addItemToInventory(string item) { // �κ��丮�� ������ �߰�
	inventory.push_back(item);
	cout << "[" << item << "]" << " added to inventory." << endl;
}

void Player::displayInventory() { // �κ��丮 ���
	if (inventory.empty())
		cout << "Inventory is empty." << endl;
	else {
		for (const auto& item : inventory)
			cout << item << " ";
		cout << endl;
	}
}

void Player::addMonToMonList(oopmon newMon) { // ����Ʈ�� ���� �߰�
	if (monList.size() < 6) {
		monList.push_back(newMon);
		cout << "[" << newMon.getName() << "]" << " added to your oopmon list!" << endl;
	}
	else cout << "The list is full. Cannot add more oopmon." << endl;
}

void Player::displayMonList() { // ���� ����Ʈ ���
	if (monList.empty())
		cout << "List is empty." << endl;
	else {
		for (int i = 0; i < monList.size(); i++) {
			cout << i + 1 << " [" << monList[i].getName() << "]"
				<< " Lv. " << monList[i].getLv() << " |"
				<< " HP: " << monList[i].getHp() << " |"
				<< " MP: " << monList[i].getMp() << endl;
		}
	}
}

oopmon& Player::curmon() { // �÷��̾ ������ ���͸� ����
	if (curMonIndex >= 0 && curMonIndex < monList.size())
		return monList[curMonIndex];
}