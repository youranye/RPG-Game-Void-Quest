#pragma once
#include "Character.h"
#include <string>
using namespace std;


enum ClassType { ROGUE, PALADIN, WARLOCK, FORGED};

class Player : public Character
{
private:
	ClassType Class_Type;
	int sp;
	const int maxSP;
	Player() : Character(), Class_Type(FORGED), sp(0), maxSP(0) {}
public:
	Player(string name, SpeciesType species, ClassType class_Type, int health, int maxsp);
	ClassType getClass();
	int getSP();
	const int getMaxSP();
	void spendSP(int amount);
	void regenerateSP(int amount);
};
