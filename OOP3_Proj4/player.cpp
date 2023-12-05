#include "Player.h"
#include <iostream>
#include <string>
#include <vector>

Player::Player(string name, string monName, montype monType) {
	this->name = name;

	oopmon firstMon(monName, monType, 1);
	this->monList.push_back(firstMon);  // 첫번째 몬스터를 리스트에 추가

	curMonIndex = 0;
	curr_maplv = 1;
}

Player::Player(const Player& other) { // 복사 생성자
	this->name = other.name;
	this->inventory = vector<string>(other.inventory);
	this->monList = vector<oopmon>(other.monList);
	this->curMonIndex = other.curMonIndex;
	this->curr_maplv = other.curr_maplv;
}

void Player::displayPlayerInfo() { // 플레이어 정보 출력
	cout << "Player Name: " << name << endl;
	cout << "Oopmon List: " << endl;
	displayMonList();
	cout << "Inventory: ";
	displayInventory();
}

void Player::addItemToInventory(string item) { // 인벤토리에 아이템 추가
	inventory.push_back(item);
	cout << "[" << item << "]" << " added to inventory." << endl;
}

void Player::displayInventory() { // 인벤토리 출력
	if (inventory.empty())
		cout << "Inventory is empty." << endl;
	else {
		for (const auto& item : inventory)
			cout << item << " ";
		cout << endl;
	}
}

void Player::addMonToMonList(oopmon newMon) { // 리스트에 몬스터 추가
	if (monList.size() < 6) {
		monList.push_back(newMon);
		cout << "[" << newMon.getName() << "]" << " added to your oopmon list!" << endl;
	}
	else cout << "The list is full. Cannot add more oopmon." << endl;
}

void Player::displayMonList() { // 몬스터 리스트 출력
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

oopmon& Player::curmon() { // 플레이어가 선택한 몬스터를 전달
	if (curMonIndex >= 0 && curMonIndex < monList.size())
		return monList[curMonIndex];
}