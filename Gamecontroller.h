#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include<string.h>
#include "Oopmon.h"
#include "player.cpp"

//gamecontroller

class gamecontroller {
public:
	gamecontroller(const Player& player);
	void battle();

private:
	Player player; // player object
	oopmon* create(int maplv);
	void npccontrol(oopmon& npcmon, oopmon& op);
};


#endif