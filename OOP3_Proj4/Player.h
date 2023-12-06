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

	void displayPlayerInfo();				// 플레이어 정보 출력
	void addItemToInventory(string item);	// 인벤토리에 아이템 추가
	void displayInventory();				// 인벤토리 출력
	void addMonToMonList(oopmon newMon);	// 리스트에 몬스터 추가
	void displayMonList();					// 몬스터 리스트 출력
	
	oopmon& curmon();						// 플레이어가 현재 선택 중인 몬스터

	int getMapLv() { return curr_maplv; }	// curr_maplv의 getter

private:
	string name; // name of player
	vector<string> inventory;
	vector<oopmon> monList;
	int curMonIndex; // 플레이어가 현재 선택 중인 몬스터의 인덱스
	int curr_maplv; // 플레이어가 현재 위치한 맵의 레벨

};

#endif