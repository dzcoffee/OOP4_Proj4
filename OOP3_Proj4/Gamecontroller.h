#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Oopmon.h"
#include "Player.h"
#include "SideWindow.h"
#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_


//gamecontroller

class gamecontroller {
public:
	gamecontroller(Player& player);
	void battle();
	void draw(sf::RenderWindow& window);
	bool isActivate();
	void enter();

private:
	Player& player; // player object
	oopmon* create(int maplv);
	void npccontrol(oopmon& npcmon, oopmon& op);
	SideWindow sideWindow;
	bool inBattle = false;
};


#endif