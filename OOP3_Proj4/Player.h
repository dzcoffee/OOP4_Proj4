#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Oopmon.h"
#include "SideWindow.h"
#include "Gamecontroller.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Player {
public:

	Player(string name, string monName, montype monType);
	Player(const Player& other);

	void displayPlayerInfo();				// �÷��̾� ���� ���
	void addMonToMonList(oopmon newMon);	// ����Ʈ�� ���� �߰�
	void displayMonList();					// ���� ����Ʈ ���
	void selectCurMon();					// �÷��̾ ����� ���� ����

	oopmon& curmon();						// �÷��̾ ���� ���� ���� ����
	int getMapLv() { return curr_maplv; }	// curr_maplv�� getter

	void setGameController(gamecontroller* gc) { this->gc = gc; } // setter of gc

private:
	string name; // name of player
	vector<oopmon> monList;
	int curMonIndex; // �÷��̾ ���� ���� ���� ������ �ε���
	int curr_maplv; // �÷��̾ ���� ��ġ�� ���� ����

	gamecontroller* gc; // gamecontroller ��ü gc�� ���� ������. sideWindow �ҷ����� ����

};

#endif