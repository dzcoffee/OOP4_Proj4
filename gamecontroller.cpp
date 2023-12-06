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

bool gamecontroller::isActivate() {
	return sideWindow.getActivate();
}

void gamecontroller::draw(sf::RenderWindow& window) {
	sideWindow.draw(window);
}

void gamecontroller::fight(int select, oopmon* npcmon) {
	switch (select) {
	case 1:
		player.curmon().tackle(*npcmon);
		sideWindow.updateText(player.curmon().getOutput());
		npccontrol(*npcmon, player.curmon());
		sideWindow.updateText(npcmon->getOutput());
		break;
	case 2:
		player.curmon().lightatk(*npcmon);
		sideWindow.updateText(player.curmon().getOutput());
		npccontrol(*npcmon, player.curmon());
		sideWindow.updateText(npcmon->getOutput());
		break;
	case 3:
		player.curmon().heavyatk(*npcmon);
		sideWindow.updateText(player.curmon().getOutput());
		npccontrol(*npcmon, player.curmon());
		sideWindow.updateText(npcmon->getOutput());
		break;
	case 4:
		player.curmon().critup();
		sideWindow.updateText(player.curmon().getOutput());
		npccontrol(*npcmon, player.curmon());
		sideWindow.updateText(npcmon->getOutput());
		break;
	case 5:
		player.curmon().evadup();
		sideWindow.updateText(player.curmon().getOutput());
		npccontrol(*npcmon, player.curmon());
		sideWindow.updateText(npcmon->getOutput());
		break;
	case 6:
		player.curmon().itemuse();
		sideWindow.updateText(player.curmon().getOutput());
		npccontrol(*npcmon, player.curmon());
		sideWindow.updateText(npcmon->getOutput());
		break;
	}
}

void gamecontroller::battle() { // if player encounters battle
	oopmon* npcmon = create(2); // create an oopmon based on the map lv where the player is in.
	string strinput = (*npcmon).getName() + " appeared!\n";
	sideWindow.updateText(strinput);
	inBattle = true;
	sideWindow.setEnable();
	
	while ((player.curmon().getHp() != 0) && (npcmon->getHp() != 0)) {
		fight(sideWindow.getFocused(), npcmon);
	}
	
	if (npcmon->getHp() <= 0) {
		sideWindow.updateText(npcmon->getName() + "'s hp is 0!\n");
		player.curmon().setExp(*npcmon);
		if (player.curmon().getExp() >= player.curmon().getExp()) {
			player.curmon().setLvup();
			sideWindow.updateText(player.curmon().getName() + " leveled up!\n");
		}
		player.addMonToMonList(*npcmon);
		sideWindow.updateText("you've captured " + npcmon->getName() +"!\n");
	}
	if (player.curmon().getHp() <= 0) {
		sideWindow.updateText(player.curmon().getName()+ " fainted!!\n");
	}
	
}

void gamecontroller::enter() {
	if (inBattle) {
		sideWindow.updateText("Battle ends!");
		sideWindow.setDisable();
		inBattle = false;
	}
	else {
		
	}
}

void gamecontroller::selectionUp() {
	sideWindow.focusUp();
}

void gamecontroller::selectionDown() {
	sideWindow.focusDown();
}

oopmon* gamecontroller::create(int maplv) { // create oopmon
	return new oopmon(maplv);	
}

void gamecontroller::npccontrol(oopmon&npcmon, oopmon& op) { // control the battle of npc oopmon (oponent)
	//check it's hp & mp first
	if (static_cast<double>(npcmon.getHp()) / static_cast<double>(npcmon.getMaxHp()) >= 0.5) { //if npcmon's hp is more than 50%
		if (npcmon.getMp() >= npcmon.getMaxMp() * 0.5) { npcmon.heavyatk(op); } // sufficient mana to heavyatk
		else if (npcmon.getMp() >= npcmon.getMaxMp() * 0.3) { npcmon.lightatk(op); } // less mana so can do lightatk
		else { npcmon.tackle(op); }//no mana, can only do tackle
	}
	else{ //if npcmon's hp is less than 50%
		if (npcmon.getMp() >= npcmon.getMaxMp() * 0.15) { npcmon.evadup(); }// if npcmon's mp is sufficient to use evad up, use it.
		else { npcmon.tackle(op); } // no mana and hp. only can do tackle
	}
}


