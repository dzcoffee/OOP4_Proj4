#include "oopmon.h"

class Player {
public:
	Player() {}
	Player(string name) : name(name) {}

	void displayPlayerInfo() { // �÷��̾� ���� ���
		cout << "Player Name: " << name << endl;
		cout << "Oopmon List: " << endl;
		displayMonList();
		cout << "Inventory: ";
		displayInventory();
	}

	void addItemToInventory(string item) { // �κ��丮�� ������ �߰�
		inventory.push_back(item);
		cout << "[" << item << "]" << " added to inventory." << endl;
	}

	void displayInventory() { // �κ��丮 ���
		if (inventory.empty())
			cout << "Inventory is empty." << endl;
		else {
			for (const auto& item : inventory)
				cout << item << " ";
			cout << endl;
		}
	}

	void addMonToMonList(oopmon newMon) { // ����Ʈ�� ���� �߰�
		if (monList.size() < 6) {
			monList.push_back(newMon);
			cout << "[" << newMon.getName() << "]" << " added to your oopmon list!" << endl;
		}
		else cout << "The list is full. Cannot add more oopmon." << endl;
	}

	void displayMonList() { // ���� ����Ʈ ���
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

	void orderBattle(oopmon* op) { // ���� ����
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