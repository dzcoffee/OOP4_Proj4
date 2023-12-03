#include "oopmon.h"

class Player {
public:
	Player() {}
	Player(string name) : name(name) {}

	void displayPlayerInfo() { // 플레이어 정보 출력
		cout << "Player Name: " << name << endl;
		cout << "Oopmon List: " << endl;
		displayMonList();
		cout << "Inventory: ";
		displayInventory();
	}

	void addItemToInventory(string item) { // 인벤토리에 아이템 추가
		inventory.push_back(item);
		cout << "[" << item << "]" << " added to inventory." << endl;
	}

	void displayInventory() { // 인벤토리 출력
		if (inventory.empty())
			cout << "Inventory is empty." << endl;
		else {
			for (const auto& item : inventory)
				cout << item << " ";
			cout << endl;
		}
	}

	void addMonToMonList(oopmon newMon) { // 리스트에 몬스터 추가
		if (monList.size() < 6) {
			monList.push_back(newMon);
			cout << "[" << newMon.getName() << "]" << " added to your oopmon list!" << endl;
		}
		else cout << "The list is full. Cannot add more oopmon." << endl;
	}

	void displayMonList() { // 몬스터 리스트 출력
		int cnt = 1;
		if (monList.empty())
			cout << "List is empty." << endl;
		else {
			for (auto& op : monList) {
				cout << cnt++ << " [" << op.getName() << "]"
					 << " Lv. " << op.getLv() << " |"
					 << " HP: " << op.getHp() << " |"
					 << " MP: " << op.getMp() << endl;
			}
		}
	}

	void orderBattle(oopmon* op) { // 전투 지시
		int selectedMon;

		cout << "Oopmon List: " << endl;
		displayMonList();
		cout << "Inventory: ";
		displayInventory();

		cout << "Which Monster do you want to choose to fight? ";
		cin >> selectedMon;
		monList[selectedMon - 1].fight(op);
	}

private:
	string name; // name of player
	vector<string> inventory;
	vector<oopmon> monList;

};