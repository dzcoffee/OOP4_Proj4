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

	void displayPlayerInfo();				// 플레이어 정보 출력
	void addMonToMonList(oopmon newMon);	// 리스트에 몬스터 추가
	void displayMonList();					// 몬스터 리스트 출력
	void selectCurMon();					// 플레이어가 사용할 몬스터 선택

	oopmon& curmon();						// 플레이어가 현재 선택 중인 몬스터
	int getMapLv() { return curr_maplv; }	// curr_maplv의 getter

	void setGameController(gamecontroller* gc) { this->gc = gc; } // setter of gc

private:
	string name; // name of player
	vector<oopmon> monList;
	int curMonIndex; // 플레이어가 현재 선택 중인 몬스터의 인덱스
	int curr_maplv; // 플레이어가 현재 위치한 맵의 레벨

	gamecontroller* gc; // gamecontroller 객체 gc에 대한 포인터. sideWindow 불러오기 위함

};

#endif