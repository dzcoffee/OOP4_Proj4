#include<iostream>
#include<stdlib.h>
#include<random>
#include<string>
#include "Oopmon.h"

using namespace std;

oopmon::oopmon(string name, enum type, int lv) { //player's first oopmon select.
	this->NAME = name;
	this->type = type;
	this->LV = lv;
	this->MAX_HP = lv * 100; this->HP = MAX_HP;
	this->MAX_MP = lv * 100; this->MP = MAX_MP;
	this->ATK = lv * 10 * 2;
	this->DEF = lv * 10 * 2;
	this->MAX_EXP = lv * 10;
	CRIT = 0.05;
	EVAD = 0.05;
	state = true;
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
	CRIT = 0.05;
	EVAD = 0.05;
	state = true;
}

void oopmon::fight(oopmon& op) { // battle command used by player object when combat
	this->setCrit(0.05); this->setEvad(0.05); // reset the value buffs before the battle
	int playerselect;
	cout << "choose your action!" << endl;
	cout << "1. Tackle\n2. Light attack\n3. Heavy attack\n 4. Crit up\n5. Evade up\n 6. item";
	cin >> playerselect;
	switch (playerselect) {
	case 1:
		tackle(op);
		break;
	case 2:
		lightatk(op);
		break;
	case 3:
		heavyatk(op);
		break;
	case 4:
		critup();
		break;
	case 5:
		evadup();
		break;
	case 6:
		itemuse();
		break;
	default:
		cout << "Wrong input! choose again\n";
		break;
	}
}

void oopmon::tackle(oopmon& op) { // default atk can used without mp, not affected by type
	int dmg = dmgCalc(this->ATK, op.getDef(), this->CRIT, op.getEvad(), this->type, op.getType(), this->HP * 0.2);
	cout << this->getName() << " used tackle!" << endl;
	cout << this->getName() << " deal " << dmg << "to " << op.getName() << endl;
	if (dmg == 0) { cout << "it was not effective!" << endl; }
	this->MP -= MAX_MP * 0.1;
	op.dmgHp(dmg);
}

void oopmon::lightatk(oopmon& op) { // high crit change, low default dmg
	int dmg = dmgCalc(this->ATK, op.getDef(), this->CRIT + 0.3, op.getEvad(), this->type, op.getType(), this->HP * 0.25);
	cout << this->getName() << " used light attack!" << endl;
	cout << this->getName() << " deal " << dmg << "to " << op.getName() << endl;
	if (dmg == 0) { cout << "it was not effective!" << endl; }
	this->MP -= MAX_MP * 0.3;
	op.dmgHp(dmg);
}

void oopmon::heavyatk(oopmon& op) { // low crit chance, high default dmb
	int dmg = dmgCalc(this->ATK, op.getDef(), this->CRIT, op.getEvad(), this->type, op.getType(), this->HP * 0.5);
	cout << this->getName() << " used heavy atk!" << endl;
	cout << this->getName() << " deal " << dmg << "to " << op.getName() << endl;
	if (dmg == 0) { cout << "it was not effective!" << endl; }
	this->MP -= MAX_MP * 0.5;
	op.dmgHp(dmg);
}

void oopmon::critup() { // self buff to crit
	cout << this->getName() << " used Crit up!" << endl;
	cout << this->getName() << "'s crit is increased by 50%!" << endl;
	this->CRIT += 50;
}

void oopmon::evadup() { // self buff to evad
	cout << this->getName() << " used Evad up!" << endl;
	cout << this->getName() << "'s Evad is increased by 50%!" << endl;
	this->EVAD += 50;
}

void oopmon::itemuse() {
	cout << this->getName() << " used bandage!" << endl;
	cout << this->NAME << " recovered 50% health!" << endl;
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