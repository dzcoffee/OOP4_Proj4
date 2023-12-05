#include <stdlib.h>
#include <random>
#include "Oopmon.h"
#include "SideWindow.h"

using namespace std;

oopmon::oopmon(string name, montype type, int lv) { //player's first oopmon select.
	this->NAME = name;
	this->type = type;
	this->LV = lv;
	this->MAX_HP = lv * 100; this->HP = MAX_HP;
	this->MAX_MP = lv * 100; this->MP = MAX_MP;
	this->ATK = lv * 10 * 2;
	this->DEF = lv * 10 * 2;
	this->MAX_EXP = lv * 10;
	this->CUR_EXP = 0;
	CRIT = 0.05;
	EVAD = 0.05;
	state = true;
	sideWindow = new SideWindow();
}
oopmon::oopmon(int lv) { //constructor, used by gamemaster object to generate oopmon
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> distribution(0, 2);
	int randnum = distribution(gen);
	switch (randnum) { // set the type of npcmon randomly
	case 0:this->type = grass; break;
	case 1:this->type = fire; break;
	case 2:this->type = water; break;
	}

	this->NAME = "wild creature" + randnum;
	this->LV = lv;
	this->MAX_HP = lv * 100; this->HP = MAX_HP;
	this->MAX_MP = lv * 100; this->MP = MAX_MP;
	this->ATK = lv * 10 * (1 + randnum);
	this->DEF = lv * 10 * (3 - randnum);
	this->MAX_EXP = lv * 10;
	this->CUR_EXP = 0;
	CRIT = 0.05;
	EVAD = 0.05;
	state = true;
	sideWindow = new SideWindow();
}

void oopmon::fight(oopmon& op) { // battle command used by player object when combat
	this->setCrit(0.05); this->setEvad(0.05); // reset the value buffs before the battle
	//sideWindow->updateText("Choose your action!\n1. Tackle\n2. Light attack\n3. Heavy attack\n 4. Crit up\n5. Evade up\n 6. item");
	//sideWindow->draw(mainwindow); // draw at mainwindow
	//sideWindow->display();
	sf::Event event;
	switch (event.key.code) {
	case sf::Keyboard::Num1:
		tackle(op);
		break;
	case sf::Keyboard::Num2:
		lightatk(op);
		break;
	case sf::Keyboard::Num3:
		heavyatk(op);
		break;
	case sf::Keyboard::Num4:
		critup();
		break;
	case sf::Keyboard::Num5:
		evadup();
		break;
	case sf::Keyboard::Num6:
		itemuse();
		break;
	default:
		//sideWindow->updateText("Wrong input! Choose again");
		//sideWindow->draw(mainwindow);
		//sideWindow->display();
		break;
	}
}

void oopmon::setLvup() { //when lv up occurs.
	this->LV += CUR_EXP / MAX_EXP;
	this->CUR_EXP -= this->MAX_EXP;
	this->MAX_EXP = this->LV * 10;
}

void oopmon::tackle(oopmon& op) { // default atk can used without mp
	int dmg = dmgCalc(this->ATK, op.getDef(), this->CRIT, op.getEvad(), this->type, op.getType(), this->HP * 0.2);
	string message = this->getName() + " used tackle!\n" + this->getName() + " dealt " + to_string(dmg) + " to " + op.getName() + "\n";
	if (dmg == 0) { message += "It was not effective!\n"; }
	op.dmgHp(dmg);
	//sideWindow->updateText(message);
	//sideWindow->draw(mainwindow);
	//sideWindow->display();
}

void oopmon::lightatk(oopmon& op) { // high crit change, low default dmg
	int dmg = dmgCalc(this->ATK, op.getDef(), this->CRIT + 0.3, op.getEvad(), this->type, op.getType(), this->HP * 0.25);
	string message = this->getName() + " used light attack!\n" + this->getName() + " dealt " + to_string(dmg) + " to " + op.getName() + "\n";
	if (dmg == 0) { message += "It was not effective!\n"; }
	this->MP -= MAX_MP * 0.3;
	op.dmgHp(dmg);
	//sideWindow->updateText(message);
	//sideWindow->draw(mainwindow);
	//sideWindow->display();
}

void oopmon::heavyatk(oopmon& op) { // low crit chance, high default dmg
	int dmg = dmgCalc(this->ATK, op.getDef(), this->CRIT, op.getEvad(), this->type, op.getType(), this->HP * 0.5);
	string message = this->getName() + " used heavy atk!\n" + this->getName() + " dealt " + to_string(dmg) + " to " + op.getName() + "\n";
	if (dmg == 0) { message += "It was not effective!\n"; }
	this->MP -= MAX_MP * 0.5;
	op.dmgHp(dmg);
	//sideWindow->updateText(message);
	//sideWindow->draw(mainwindow);
	//sideWindow->display();
}

void oopmon::critup() { // self buff to crit
	string message = this->getName() + " used Crit up!\n" + this->getName() + "'s crit is increased by 50%!\n";
	//sideWindow->updateText(message);
	//sideWindow->draw(mainwindow);
	//sideWindow->display();
	this->MP -= MAX_MP * 0.15;
	this->CRIT += (1.0 - this->getCrit()) / 2;
}

void oopmon::evadup() { // self buff to evad
	string message = this->getName() + " used Evad up!\n" + this->getName() + "'s Evad is increased!\n";
	//sideWindow->updateText(message);
	//sideWindow->draw(mainwindow);
	//sideWindow->display();
	this->MP -= MAX_MP * 0.15;
	this->EVAD += (1.0 - this->getEvad()) / 2;
}

void oopmon::itemuse() {
	string message = this->getName() + " used bandage!\n" + this->getName() + " recovered 50% health!\n";
	//sideWindow->updateText(message);
	//sideWindow->draw(mainwindow);
	//sideWindow->display();
	this->dmgHp(-50 * this->MAX_HP);
}

int oopmon::dmgCalc(int atk, int def, double CRIT, double EVAD, int thistype, int thattype, double skilldmg) { //calculate crit & evasion of the attack
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> distribution(1, 100);
	int randnum = distribution(gen);//get random number b/w 1~100 to calculate evade & crit

	int typedif = thistype - thattype; double typevalue; // setting type diffrence and calculate dmg coefficient 
	if (typedif < 0) {
		if (abs(typedif) == 1) { typevalue = 0.5; }
		else { typevalue = 2; }
	}
	else {
		if (abs(typedif) == 1) { typevalue = 2; }
		else { typevalue = 0.5; }
	}

	if (randnum < EVAD * 100) { return 0; } // if evad occur, evade normal and crit attack.
	else if (randnum > CRIT * 100 && randnum > EVAD * 100) { return atk * skilldmg * typevalue - def; } // didn't crit nor evade. deal normal dmg
	else if (randnum <CRIT * 100 && randnum > EVAD * 100) { return atk * skilldmg * typevalue * 2 - def; } // can't evade. deal crit dmg
}