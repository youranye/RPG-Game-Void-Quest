#pragma once
#include "Character.h"

using namespace std;


enum Religion { TRAVELER, NOTHING, SHADOW, FORGE, SILVER};
enum ClassType { ROGUE, PALADIN, WARLOCK, FORGED};

class Player : public Character
{
private:
	ClassType Class_Type;
	Religion religion;
	int sp;
	const int maxSP;
	int level;
public:
	Player() : Character(), Class_Type(FORGED), religion(NOTHING), sp(0), maxSP(0), level(0) {}
	Player(string name, SpeciesType species, CharacterType Character_Type, ClassType class_type, Religion Religion_, int health, int maxsp);
	ClassType get_class();
	int get_sp();
	void spend_sp(int amount);
	void regenerate_sp(int amount);
	Ability levelup();
};

