#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include <string.h>
#include "Oopmon.h"
#include "Player.h"
#include "SideWindow.h"

//gamecontroller

class gamecontroller {
public:
	gamecontroller(const Player& player);
	void battle();

	SideWindow* getSideWindow() { return sideWindow; }

private:
	Player player; // player object
	oopmon* create(int maplv);
	void npccontrol(oopmon& npcmon, oopmon& op);

	SideWindow* sideWindow; // πË∆≤ √¢
};


#endif