#include "Oopmon.h"
#include"player.cpp"
#include "Gamecontroller.h"
#include"Map.cpp"
#include<iostream>
#include<string.h>
#include<vector>

using namespace std;

gamecontroller::gamecontroller(const Player& player) {
	this->player = player;
};

void gamecontroller::battle() { // if player encounters battle
	oopmon *npcmon = create(player.curr_maplv); // create an oopmon based on the map lv where the player is in.
	while (player.curmon().getHp() && npcmon->getHp()) { // while neither player or npc's mop is alive
		player.curmon().fight(*npcmon); //player's turn
		npccontrol(*npcmon, player.curmon()); // npc's turn
	}

	if (npcmon->getHp() == 0) { // the battle ends and if player won
		if (npcmon->getHp() <= 0) { cout << npcmon->getName() << "'s hp is 0!\n";}
		player.addMonToMonList(*npcmon); // add the npcmon into player's monlist
	}
	else { cout << player.curmon().getName() << " Faded!" << endl; } //if player lose
	cout << "battle ends!" << endl;
}

oopmon* gamecontroller::create(int maplv) { // create oopmon
	return new oopmon(maplv);	
}

void gamecontroller::npccontrol(oopmon&npcmon, oopmon& op) { // control the battle of npc oopmon (oponent)

	//need more precise logic for npc oopmon's action choice

	if (npcmon.getHp() / npcmon.getMaxHp() >= 0.5) npcmon.heavyatk(op); // if hp of npc mon is higher than 50%, use heavyatk to player's mon
	if (npcmon.getHp() / npcmon.getMaxHp() < 0.5 && npcmon.getHp() / npcmon.getMaxHp() >= 0.3) npcmon.lightatk(op);
	if (npcmon.getHp() / npcmon.getMaxHp() < 0.3) npcmon.evadup(); // if hp of npc mon is low, try to evade up
}
