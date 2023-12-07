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
	void fight(int select);
	void battle();
	void draw(sf::RenderWindow& window);
	bool isActivate();
	void enter();
	void selectionUp();
	void selectionDown();
	void selectionLeft();
	void selectionRight();
	void setCenter(float x, float y);
private:
	Player& player; // player object
	oopmon enemy;
	void create(int maplv);
	void npccontrol(oopmon& npcmon, oopmon& op);
	SideWindow sideWindow;
	bool inBattle = false;
	bool myTurn = false;
};


#endif