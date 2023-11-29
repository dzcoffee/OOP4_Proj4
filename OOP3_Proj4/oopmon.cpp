#include<iostream>
#include<stdlib.h>
#include<random>
#include<string>

using namespace std;

class oopmon {
public:
	enum montype { grass, fire, water }; //grass==0, fire==1, water==2

	oopmon() {}
	oopmon(string name) { this->NAME = name; }
	oopmon(montype type) {	this->type = type;}
	oopmon(string name, montype type, int lv, int atk, int def) { //constructor, used by gamemaster object to generate oopmon
		this->NAME = name;
		this->type = type;
		this->LV = lv;
		this->MAX_HP = lv * 100; this->HP = MAX_HP;
		this->MAX_MP = lv * 100; this->MP = MAX_MP;
		this->ATK = atk;
		this->DEF = def;
		this->MAX_EXP = lv * 10;
		CRIT = 0.05;
		EVAD = 0.05;
		state = true;
	}

	void fight(oopmon* op) { // battle command used by player object when combat
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

	//getter
	string getName() { return this->NAME; }
	int getHp() { return this->HP; }
	int getMp() { return this->MP; }
	int getAtk() { return this->ATK; }
	int getDef() { return this->DEF; }
	int getCrit() { return this->CRIT; }
	int getEvad() { return this->EVAD; }
	int getLv() { return this->LV; }
	int getType() { return this->type; }

	//setter
	void setHp(int value) { this->HP = value; } // used for revive
	void setMp(int value) { this->MP = value; } //used for revive
	void setCrit(int value) { this->CRIT = value; } // used for reset after battle
	void setEvad(int value) { this->EVAD = value; } // used for reset after battle

	//dmg calc
	void dmgHp(int value) { this->HP -= value; } // used to dmg or heal health by amount
	void useMp(int value) { this->MP -= value; } // used to charge used mana by amount

private:
	string NAME; //name of oopmon
	int HP; //current health
	int MP; //current mana
	int MAX_HP; //max health
	int MAX_MP; //max mana
	int ATK; 
	int DEF; 
	int LV;
	int CUR_EXP; //current exp gathered
	int MAX_EXP; //exp amount need to lv up
	double CRIT;
	double EVAD;
	bool state; // alive == true, dead == false
	montype type; //fire deals grass by 2*dmg, water deals fire by 2*dmg, grass deals water by 2*dmg. coresponding oponents deals only  0.5*dmg

	void tackle(oopmon* op) { // default atk can used without mp, not affected by type
		int dmg = dmgCalc(this->ATK, op->getDef(), this->CRIT, op->getEvad(), this->type,op->getType(), this->HP * 0.2);
		cout << "you used tackle!" << endl;
		cout << "you deal "<<  dmg <<"to "<< op->getName() << endl;
		if (dmg == 0) { cout << "it was not effective!"<<endl; }
		this->MP -=MAX_MP*0.1;
		op->dmgHp(dmg);
	}

	void lightatk(oopmon* op) { // high crit change, low default dmg
		int dmg = dmgCalc(this->ATK, op->getDef(), this->CRIT+0.3, op->getEvad(), this->type,op->getType(), this->HP * 0.25);
		cout << "you used light attack!" << endl;
		cout << "you deal " << dmg << "to " << op->getName() << endl;
		if (dmg == 0) { cout << "it was not effective!" << endl; }
		this->MP -= MAX_MP * 0.3;
		op->dmgHp(dmg);
	}

	void heavyatk(oopmon* op) { // low crit chance, high default dmb
		int dmg = dmgCalc(this->ATK, op->getDef(), this->CRIT, op->getEvad(), this->type, op->getType(), this->HP * 0.5);
		cout << "you used heavy atk!" << endl;
		cout << "you deal " << dmg << "to " << op->getName() << endl;
		if (dmg == 0) { cout << "it was not effective!" << endl; }
		this->MP -= MAX_MP * 0.5;
		op->dmgHp(dmg);
	}

	void critup() { // self buff to crit
		cout << "you used Crit up!" << endl;
		cout << "your crit is increased by 50%!" << endl;
		this->CRIT += 50;
	}

	void evadup() { // self buff to evad
		cout << "you used Evad up!" << endl;
		cout << "your Evad is increased by 50%!" << endl;
		this->EVAD += 50;
	}

	void itemuse() {
		cout << "you used bandage!" << endl;
		cout << this->NAME << " recovered 50% health!" << endl;
		this->dmgHp(-50 * this->MAX_HP);
	}
	
	int dmgCalc(int atk, int def, double CRIT, double EVAD, int thistype, int thattype, double skilldmg) { //calculate crit & evasion of the attack
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> distribution(1, 100); 
		int randnum = distribution(gen);//get random number b/w 1~100 to calculate evade & crit
		
		int typedif=thistype-thattype; double typevalue; // setting type diffrence and calculate dmg coefficient 
		if (typedif < 0) {
			if(abs(typedif)==1){ typevalue = 0.5; }
			else{ typevalue = 2; }
		}
		else {
			if (abs(typedif) == 1) { typevalue = 2; }
			else { typevalue = 0.5; }
		}
		
		if (randnum < EVAD * 100) { return 0; } // if evad occur, evade normal and crit attack.
		else if (randnum > CRIT * 100 && randnum > EVAD * 100) { return atk*skilldmg*typevalue-def; } // didn't crit nor evade. deal normal dmg
		else if (randnum <CRIT * 100 && randnum > EVAD * 100) { return atk*skilldmg*typevalue * 2-def; } // can't evade. deal crit dmg
	}
};