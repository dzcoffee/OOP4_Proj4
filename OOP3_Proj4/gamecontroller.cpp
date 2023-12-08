#include "Oopmon.h"
#include "Player.h"
#include "Gamecontroller.h"
#include "Map.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

gamecontroller::gamecontroller(Player& player) : player(player), enemy(0) {
	//this->player = player;
};

bool gamecontroller::isActivate() {
	return sideWindow.getActivate();
}

void gamecontroller::draw(sf::RenderWindow& window) {
	sideWindow.draw(window);
}

void gamecontroller::fight(int select) {
	switch (select) {
	case 1:
		player.curmon().tackle(enemy);
		sideWindow.updateText(player.curmon().getOutput());
		break;
	case 2:
		player.curmon().lightatk(enemy);
		sideWindow.updateText(player.curmon().getOutput());
		break;
	case 3:
		player.curmon().heavyatk(enemy);
		sideWindow.updateText(player.curmon().getOutput());
		break;
	case 4:
		player.curmon().critup();
		sideWindow.updateText(player.curmon().getOutput());
		break;
	case 5:
		player.curmon().evadup();
		sideWindow.updateText(player.curmon().getOutput());
		break;
	case 6:
		player.curmon().itemuse();
		sideWindow.updateText(player.curmon().getOutput());
		break;
	}
}

void gamecontroller::battle() { // if player encounters battle
	create(player.getMapLv()); // create an oopmon based on the map lv where the player is in.
	inBattle = true;
	myTurn = true;
	sideWindow.setEnable(&player.curmon(), &enemy);
	string strinput = enemy.getName() + " appeared!\n";
	sideWindow.updateText(strinput);
}

void gamecontroller::enter() {
	if (inBattle) {
		if (myTurn) {
			fight(sideWindow.getFocused());
			sideWindow.update();
			if (enemy.getHp() <= 0) {
				sideWindow.appendText(enemy.getName() + "'s hp is 0!\n");
				player.curmon().setExp(enemy);
				if (player.curmon().iflvup()) {
					player.curmon().setLvup();
					sideWindow.appendText(player.curmon().getName() + " leveled up!\n");
				}
				player.addMonToMonList(enemy);
				sideWindow.appendText("you've captured " + enemy.getName() + "!\n");
				inBattle = false;
			}
			myTurn = false;
		}
		else {
			npccontrol(enemy, player.curmon());
			sideWindow.updateText(enemy.getOutput());
			sideWindow.update();
			if (player.curmon().getHp() <= 0) {
				sideWindow.appendText(player.curmon().getName() + " fainted!!\n");
				inBattle = false;
			}
			myTurn = true;
		}
	}
	else {
		sideWindow.setDisable();
	}
}

void gamecontroller::selectionUp() {
	if (myTurn)
		sideWindow.focusUp();
}

void gamecontroller::selectionDown() {
	if (myTurn)
		sideWindow.focusDown();
}

void gamecontroller::selectionLeft() {
	if (myTurn)
		sideWindow.focusLeft();
}

void gamecontroller::selectionRight() {
	if (myTurn)
		sideWindow.focusRight();
}

void gamecontroller::create(int maplv) { // create oopmon
	enemy = oopmon(maplv);
}

void gamecontroller::npccontrol(oopmon& npcmon, oopmon& op) { // control the battle of npc oopmon (oponent)
	//check it's hp & mp first
	if (static_cast<double>(npcmon.getHp()) / static_cast<double>(npcmon.getMaxHp()) >= 0.5) { //if npcmon's hp is more than 50%
		if (npcmon.getMp() >= npcmon.getMaxMp() * 0.5) { npcmon.heavyatk(op); } // sufficient mana to heavyatk
		else if (npcmon.getMp() >= npcmon.getMaxMp() * 0.3) { npcmon.lightatk(op); } // less mana so can do lightatk
		else { npcmon.tackle(op); }//no mana, can only do tackle
	}
	else { //if npcmon's hp is less than 50%
		if (npcmon.getMp() >= npcmon.getMaxMp() * 0.15) { npcmon.evadup(); }// if npcmon's mp is sufficient to use evad up, use it.
		else { npcmon.tackle(op); } // no mana and hp. only can do tackle
	}
}

void gamecontroller::setCenter(float x, float y) {
	sideWindow.setCenter(x, y);
}