#include "Oopmon.h"
#include <iostream>
#include <string>
#include <vector>


#ifndef _PLAYER_H_
#define _PLAYER_H_

using namespace std;

class Player {
public:

	Player(string name, string monName, oopmon::montype monType);
	Player(const Player& other);

	void displayPlayerInfo();				// �÷��̾� ���� ���
	void addItemToInventory(string item);	// �κ��丮�� ������ �߰�
	void displayInventory();				// �κ��丮 ���
	void addMonToMonList(oopmon newMon);	// ����Ʈ�� ���� �߰�
	void displayMonList();					// ���� ����Ʈ ���
	
	oopmon& curmon();						// �÷��̾ ���� ���� ���� ����

	int getMapLv() { return curr_maplv; }	// curr_maplv�� getter

private:
	string name; // name of player
	vector<string> inventory;
	vector<oopmon> monList;
	int curMonIndex; // �÷��̾ ���� ���� ���� ������ �ε���
	int curr_maplv; // �÷��̾ ���� ��ġ�� ���� ����

};

#endif