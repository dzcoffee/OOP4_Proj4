#include <SFML/Graphics.hpp>
#include "oopmon.cpp"

using namespace sf;

class Player {
public:
	Player() {}
	Player(string name) : name(name) {}

	void displayPlayerInfo() { // �÷��̾� ���� ���
		cout << "Player Name: " << name << endl;
		cout << "Oopmon List: ";
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
			cout << endl;
			for (auto& op : monList) {
				cout << cnt++ << " [" << op.getName() << "]"
					<< " Lv. " << op.getLv() << " |"
					<< " HP: " << op.getHp() << " |"
					<< " MP: " << op.getMp() << endl;
			}
		}
	}

	void selectCurMon() { // �÷��̾ ���� ����� ���͸� ����
		int selectedMon;

		cout << "Oopmon List: " << endl;
		displayMonList();
		cout << "Inventory: ";
		displayInventory();

		cout << "Which Monster do you want to choose to fight? ";
		cin >> selectedMon;
		curMonIndex = selectedMon - 1;
	}

	oopmon& curmon() { // �÷��̾ ������ ���͸� ����
		if (curMonIndex >= 0 && curMonIndex < monList.size())
			return monList[curMonIndex];
		else
			cout << "There are cureently no monsters you have!" << endl;
	}

	bool isEncounted(vector<oopmon> mapmonList) { // mapmon�� �������� ���� ��ȯ
		for (int i = 0; i < 6; i++) {
			if (get_hit_box().intersects(mapmonList[i].get_hit_box())) {
				cout << "met " << mapmonList[i].getName() << "!" << endl;
				cout << "Start a battle with " << mapmonList[i].getName() << "." << endl;
				return true;
			}
		}
		return false;
	}

	sf::FloatRect get_hit_box() const;

private:
	string name; // name of player
	vector<string> inventory;
	vector<oopmon> monList;
	int curMonIndex; // index of player's current monster choice

};