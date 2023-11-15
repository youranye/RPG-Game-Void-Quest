#pragma once
#include "Character.h"

using namespace std;

class Enemy : public Character
{
private:

public:
	Enemy() : attack(0), defense(0), dexterity(0), hp(0), maxHP(0) {}
	Enemy(string name, SpeciesType species, CharacterType Character_Type, int atk, int def, int dex, int health) :
		Character(name, species, Character_Type, health), attack(atk), defense(def), dexterity(dex), hp(health) {}
};

