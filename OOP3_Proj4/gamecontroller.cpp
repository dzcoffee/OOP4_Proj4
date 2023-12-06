#include "Oopmon.h"
#include "Player.h"
#include "Gamecontroller.h"
#include "Map.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

gamecontroller::gamecontroller(Player& player) : player(player) {
	//this->player = player;
};

bool gamecontroller::inBattle() {
	return _inBattle;
}

void gamecontroller::draw(sf::RenderWindow& window) {
	sideWindow.draw(window);
}

void gamecontroller::battle() { // if player encounters battle
	oopmon *npcmon = create(player.getMapLv()); // create an oopmon based on the map lv where the player is in.
	while (player.curmon().getHp() && npcmon->getHp()) { // while either player or npc's mop is alive
		player.curmon().fight(*npcmon, sideWindow); //player's turn
		npccontrol(*npcmon, player.curmon()); // npc's turn
	}

	if (npcmon->getHp() <= 0) {
		sideWindow.updateText(npcmon->getName() + "'s hp is 0!\n");
		player.curmon().setExp(*npcmon);
		if (player.curmon().getExp() >= player.curmon().getExp()) {
			player.curmon().setLvup();
			sideWindow.updateText(player.curmon().getName() + " leveled up!\n");
		}
		player.addMonToMonList(*npcmon);
		sideWindow.updateText(player.curmon().getName() + " added " + npcmon->getName() + " to the monlist!\n");
	}
	else { sideWindow.updateText(player.curmon().getName() + " Faded!\n");}
	sideWindow.updateText("Battle ends!\n");
	//sideWindow->draw(mainwindow); // draw at mainwindow
	//sideWindow->display();
}

oopmon* gamecontroller::create(int maplv) { // create oopmon
	return new oopmon(maplv);	
}

void gamecontroller::npccontrol(oopmon&npcmon, oopmon& op) { // control the battle of npc oopmon (oponent)
	//check it's hp & mp first
	if (static_cast<double>(npcmon.getHp()) / static_cast<double>(npcmon.getMaxHp()) >= 0.5) { //if npcmon's hp is more than 50%
		if (npcmon.getMp() >= npcmon.getMaxMp() * 0.5) { npcmon.heavyatk(op, sideWindow); } // sufficient mana to heavyatk
		else if (npcmon.getMp() >= npcmon.getMaxMp() * 0.3) { npcmon.lightatk(op, sideWindow); } // less mana so can do lightatk
		else { npcmon.tackle(op, sideWindow); }//no mana, can only do tackle
	}
	else{ //if npcmon's hp is less than 50%
		if (npcmon.getMp() >= npcmon.getMaxMp() * 0.15) { npcmon.evadup(sideWindow); }// if npcmon's mp is sufficient to use evad up, use it.
		else { npcmon.tackle(op, sideWindow); } // no mana and hp. only can do tackle
	}
}


