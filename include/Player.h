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
	int attack;
	int defense;
	int dexterity;
	int hp;
	int sp;
	const int maxHP;
	const int maxSP;
	vector<Ability> abilities;
	int level;
public:
	Player() : Class_Type(FORGED), religion(NOTHING), attack(0), defense(0), dexterity(0), hp(0), sp(0), maxHP(0), maxSP(0), level(0) {}
	Player(string name, SpeciesType species, CharacterType Character_Type, ClassType class_type, Religion Religion_, int health, int maxsp);
	ClassType get_class();
	int get_attack();
	int get_defense();
	int get_dexterity();
	int get_hp();
	void heal(int amount);
	void take_damage(int amount);

	//after first commit
	Ability levelup();
};

