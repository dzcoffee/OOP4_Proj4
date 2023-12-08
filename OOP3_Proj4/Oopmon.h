#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


#ifndef _OOPMON_H_
#define _OOPMON_H_

//oopmon

class oopmon {
public:
	friend class gamecontroller;
	enum montype { grass, fire, water }; //grass==0, fire==1, water==2

	oopmon(std::string name, montype, int lv);
	oopmon(int lv);

	static const int monNum = 1;
	static std::string names[monNum];
	//void fight(oopmon& op, int choice);

	//getter
	std::string getName() { return this->NAME; }
	std::string getOutput() { return this->output; }
	int getHp() { return this->HP; }
	int getMp() { return this->MP; }
	int getMaxHp() { return this->MAX_HP; }
	int getMaxMp() { return this->MAX_MP; }
	int getAtk() { return this->ATK; }
	int getDef() { return this->DEF; }
	double getCrit() { return this->CRIT; }
	double getEvad() { return this->EVAD; }
	int getLv() { return this->LV; }
	int getExp() { return this->CUR_EXP; }
	int getMExp() { return this->MAX_EXP; }
	int getType() { return this->type; }
	bool getAlive() { return this->state; }
	bool iflvup() { return this->CUR_EXP >= this->MAX_EXP; }

	//setter
	void setHp(int value) { this->HP = value; } // used for revive
	void setMp(int value) { this->MP = value; } //used for revive
	void setCrit(int value) { this->CRIT = value; } // used for reset after battle
	void setEvad(int value) { this->EVAD = value; } // used for reset after battle
	void setState(bool state) { this->state = state; } //set state of oopmon if dead
	void setExp(oopmon& op); // get the exp if oopmon won.
	void setLvup(); // lv up if cur_exp get to the max_exp

	//dmg calc
	void dmgHp(int value) { 
		this->HP -= value;  
		if (HP <= 0) state = false;
	} // used to dmg or heal health by amount
	void useMp(int value) { this->MP -= value; } // used to charge used mana by amount


	void tackle(oopmon& op);
	int lightatk(oopmon& op);
	int heavyatk(oopmon& op);
	int critup();
	int evadup();
	int itemuse();

	int dmgCalc(int atk, int def, double CRIT, double EVAD, int thistype, int thattype, double skilldmg);
	void resurrection();
private:
	std::string NAME; //name of oopmon
	std::string output = ""; // battle result etc
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
	montype type; //fire deals grass by 2*dmg, water deals fire by 2*dmg, grass deals water by 2*dmg. corresponding oponents deals only  0.5*dmg
};


#endif