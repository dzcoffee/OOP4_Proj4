#include"oopmon.cpp"
#include"player.cpp"
#include"Map.cpp"
#include<iostream>
#include<string.h>
#include<vector>

class gamecontroller {
public:
	gamecontroller(const Player&player) {
		this->player = player;
		create();
	};

	void battle() { // if player encounters battle
		while (player.curmon().getHp() && mapmonList[0].getHp()) { // while neither player or npc's mop is alive
			player.curmon().fight(mapmonList[0]);
			mapmonList[0].fight(player.curmon());
		}
		cout << "battle ends!" << endl;
	}

private:
	vector<oopmon> mapmonList; // oopmon list of current map. scaled off with map lv or player lv
	string currmap; // current map where player is in
	Player player; // player object

	void create() { // create oopmon of the map when player entered
		for(int i=0;i<6;i++) mapmonList.push_back(oopmon(currmap.lv())); // create oopmon based on map's lv
	}
	void npccontrol() { // control the battle of npc oopmon (oponent)
		vector<oopmon>::iterator it = mapmonList.begin();
		if (mapmonList[0].getHp() / mapmonList[0].getMaxHp() >= 0.5) mapmonList[0].heavyatk(player.curmon()); // if hp of npc mon is higher than 50%, use heavyatk to player's mon
		if (mapmonList[0].getHp() / mapmonList[0].getMaxHp() <0.5 && mapmonList[0].getHp() / mapmonList[0].getMaxHp() >= 0.3) mapmonList[0].lightatk(player.curmon());
		if (mapmonList[0].getHp() / mapmonList[0].getMaxHp() < 0.3) mapmonList[0].evadup()); // if hp of npc mon is low, try to evade up
		if (mapmonList[0].getHp() <= 0) {
			cout << mapmonList[0].getName() << "'s hp is 0!\n";
			mapmonList.erase(it);
		}
	}

};