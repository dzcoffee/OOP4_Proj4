#include <stdlib.h>
#include <random>
#include "Oopmon.h"
#include "SideWindow.h"

using namespace std;

oopmon::oopmon(string name, montype type, int lv) { //player's first oopmon select.
	this->NAME = name;
	this->type = type;
	this->LV = lv;
	this->MAX_HP = lv * 400; this->HP = MAX_HP;
	this->MAX_MP = lv * 100; this->MP = MAX_MP;
	this->ATK = lv * 1 * 2;
	this->DEF = lv * 1 * 2;
	this->MAX_EXP = lv * 10;
	this->CUR_EXP = 0;
	CRIT = 0.05;
	EVAD = 0.05;
	state = true;
}
oopmon::oopmon(int lv) { //constructor, used by gamemaster object to generate oopmon
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> distribution(0, 2);
	int randnum = distribution(gen);
	string namestr;
	switch (randnum) { // set the type of npcmon randomly
	case 0:this->type = grass; namestr = "grass"; break;
	case 1:this->type = fire; namestr = "fire"; break;
	case 2:this->type = water; namestr = "water"; break;
	}

	this->NAME = "wild creature " + namestr;
	this->LV = lv + 1;
	this->MAX_HP = lv * 400; this->HP = MAX_HP;
	this->MAX_MP = lv * 100; this->MP = MAX_MP;
	this->ATK = lv * 1 * (1);
	this->DEF = lv * 1 * (3 - randnum);
	this->MAX_EXP = lv * 10;
	this->CUR_EXP = 0;
	CRIT = 0.00;
	EVAD = 0.05;
	state = true;
}

void oopmon::setExp(oopmon& op) { this->CUR_EXP += op.getExp() * 0.5; }

void oopmon::setLvup() { //when lv up occurs.
	if (this->MAX_EXP != 0) {
		this->LV += CUR_EXP / MAX_EXP;
		this->CUR_EXP -= this->MAX_EXP;
		this->MAX_EXP = this->LV * 10;
		this->MAX_HP = LV * 100; this->HP = MAX_HP;
		this->MAX_MP = LV * 100; this->MP = MAX_MP;
	}
}

void oopmon::tackle(oopmon& op) { // default atk can used without mp
	int dmg = dmgCalc(this->ATK, op.getDef(), this->CRIT, op.getEvad(), this->type, op.getType(), this->getLv() * 20);
	this->output = this->getName() + " used tackle!\n" + this->getName() + " dealt " + to_string(dmg) + " to " + op.getName() + "\n";
	if (dmg == 0) { this->output += "It was not effective!\n"; }
	op.dmgHp(dmg);
}

int oopmon::lightatk(oopmon& op) { // high crit change, low default dmg
	if (this->getMp() >= MAX_MP * 0.15) {
		int dmg = dmgCalc(this->ATK, op.getDef(), this->CRIT + 0.3, op.getEvad(), this->type, op.getType(), this->getLv() * 25);
		this->output = this->getName() + " used light attack!\n" + this->getName() + " dealt " + to_string(dmg) + " to " + op.getName() + "\n";
		if (dmg == 0) { this->output += "It was not effective!\n"; }
		this->MP -= MAX_MP * 0.15;
		op.dmgHp(dmg);
		return 0;
	}
	else this->output = "not sufficient MANA!!\n"; return 1;
}

int oopmon::heavyatk(oopmon& op) { // low crit chance, high default dmg
	if (this->getMp() >= MAX_MP * 0.2) {
		int dmg = dmgCalc(this->ATK, op.getDef(), this->CRIT, op.getEvad(), this->type, op.getType(), this->getLv() * 40);
		this->output = this->getName() + " used heavy atk!\n" + this->getName() + " dealt " + to_string(dmg) + " to " + op.getName() + "\n";
		if (dmg == 0) { this->output += "It was not effective!\n"; }
		this->MP -= MAX_MP * 0.2;
		op.dmgHp(dmg);
		return 0;
	}
	else this->output = "not sufficient MANA!!\n"; return 1;
}

int oopmon::critup() { // self buff to crit
	if (this->getMp() >= MAX_MP * 0.2) {
		this->output = this->getName() + " used Crit up!\n" + this->getName() + "'s crit is increased!\n";
		this->MP -= MAX_MP * 0.2;
		this->CRIT += (1.0 - this->getCrit()) / 4;
		this->output += "current crit is " + to_string(this->getCrit());
		return 0;
	}
	else this->output = "not sufficient MANA!!\n"; return 1;
}

int oopmon::evadup() { // self buff to evad
	if (this->getMp() >= MAX_MP * 0.2) {
		this->output = this->getName() + " used Evad up!\n" + this->getName() + "'s Evad is increased!\n";
		this->MP -= MAX_MP * 0.2;
		this->EVAD += (1.0 - this->getEvad()) / 4;
		this->output += "current evad is " + to_string(this->getEvad());
		return 0;
	}
	else this->output = "not sufficient MANA!!\n"; return 1;
}

int oopmon::itemuse() {
	if (this->getMp() >= MAX_MP * 0.15) {
		this->output = this->getName() + " used bandage!\n" + this->getName() + " recovered 50% health!\n";
		this->MP -= MAX_MP * 0.15;
		this->dmgHp(-0.5 * this->MAX_HP);
		return 0;
	}
	else this->output = "not sufficient MANA!!\n"; return 1;
}

int oopmon::dmgCalc(int atk, int def, double CRIT, double EVAD, int thistype, int thattype, double skilldmg) { //calculate crit & evasion of the attack
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> distribution(1, 100);
	int randnum = distribution(gen);//get random number b/w 1~100 to calculate evade & crit

	int typedif = thistype - thattype; double typevalue; // setting type diffrence and calculate dmg coefficient 
	if (typedif < 0) {
		if (abs(typedif) == 1) { typevalue = 0.5; }
		else { typevalue = 1.5; }
	}
	else {
		if (abs(typedif) == 1) { typevalue = 1.5; }
		else { typevalue = 0.5; }
	}

	if (randnum < EVAD * 100) { return 0; } // if evad occur, evade normal and crit attack.
	else if (randnum > CRIT * 100 && randnum > EVAD * 100) { return atk * skilldmg * typevalue - def; } // didn't crit nor evade. deal normal dmg
	else if (randnum <CRIT * 100 && randnum > EVAD * 100) { return atk * skilldmg * typevalue * 1.5 - def; } // can't evade. deal crit dmg
}

void oopmon::resurrection() {
	HP = MAX_HP;
	MP = MAX_MP;
	setCrit(0.05);
	setEvad(0.05);
	state = true;
}