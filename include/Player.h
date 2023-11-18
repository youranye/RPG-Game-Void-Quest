#pragma once
#include "Character.h"

using namespace std;


enum ClassType { ROGUE, PALADIN, WARLOCK, FORGED};

class Player : public Character
{
private:
	ClassType Class_Type;
	int sp;
	const int maxSP;
public:
	Player() : Character(), Class_Type(FORGED), sp(0), maxSP(0) {}
	Player(string name, SpeciesType species, CharacterType Character_Type, ClassType class_type, int health, int maxsp);
	ClassType get_class();
	int get_sp();
	const int get_max_sp();
	void spend_sp(int amount);
	void regenerate_sp(int amount);
};

