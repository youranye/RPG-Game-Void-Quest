#pragma once
#include "Character.h"

using namespace std;

class Enemy : public Character
{
private:
	int attack;
	int defense;
	int dexterity;
	int hp;
	const int maxHP;
	vector<Ability> abilities;
public:
	Enemy() : attack(0), defense(0), dexterity(0), hp(0), maxHP(0) {}
	Enemy(string name, SpeciesType species, CharacterType Character_Type, int atk, int def, int dex, int health) :
		Character(name, species, Character_Type), attack(atk), defense(def), dexterity(dex), hp(health),
		maxHP(health) {}
	int get_attack();
	int get_defense();
	int get_dexterity();
	int get_hp();
	void heal(int amount);
	void take_damage(int amount);
};

