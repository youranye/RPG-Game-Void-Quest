#pragma once
#include <string>
#include <vector>

using namespace std;


enum SpeciesType {HUMAN, ELF, DWARF, GOBLIN, TABAXI};
enum ClassType { ROGUE, PALADIN, WARLOCK, FORGED};

/// gonna have to create derived classes for each Player and enemy, since Enemies have different stats and Species, and no classes

class Character
{
private:
	string Name;
	SpeciesType Species;
	ClassType Class;
	int attack;
	int defense;
	int dexterity;
	int hp;
	const int maxHP;
public:
	Character(string name, SpeciesType species, ClassType clas, int atk, int def, int dex, int health) :
		Name(name), Species(species), Class(clas), attack(atk), defense(def), dexterity(dex), hp(health), maxHP(health) {}
	string get_name();
	SpeciesType get_species();
	ClassType get_class();
	int get_attack();
	int get_defense();
	int get_dexterity();
	int get_hp();
	void heal(int amount);
	void take_damage(int amount);
};
// When a function looks for a specific character and doesn't find it, it should return nullCharacter to indicate the character was not found.
#ifndef NULLCHARACTER
#define NULLCHARACTER
static Character nullCharacter("NULLCHARACTER", HUMAN, ROGUE, 0, 0, 0, 0);
#endif