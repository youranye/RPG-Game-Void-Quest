#pragma once
#include <string>
#include <vector>

using namespace std;

//character and enemy shared enums
enum SpeciesType {HUMAN, ELF, DWARF, GOBLIN, TABAXI, ORC, GOLIATH, CHANGELING, GNOME, VOIDWALKER};
//utilize to differentiate between player type character and Enemy type character
enum CharacterType {PLAYER, ENEMY, STORY};
enum AbilityType {ATTACK, DEFEND, BUFF, DEBUFF, HEAL};
enum AbilityCondition {ATK, DEF, DEX, SLEEP, CONFUSION, NONE};

//new way of handling attacks
struct Ability {
	string name;
	AbilityType type;
	string description;
	AbilityCondition condition;
	int power;
	int cost;
	int accuracy;
	Ability() : name("InvalidAbility"), type(DEBUFF), description("EMPTYABILITY"), condition(NONE), power(0), cost(0), accuracy(0) {}
	Ability(string name, AbilityType type, string desc, AbilityCondition cond, int pow, int cost, int acc) : 
		name(name), type(type), description(desc), condition(cond), power(pow), cost(cost), accuracy(acc) {}
};
//Basic Attack
//Ability ("Basic Attack", ATTACK, "Attack Enemy", NONE, 90, 0, 99)
//character is now abstract base class
class Character
{
private:
	string Name;
	SpeciesType Species;
	CharacterType type;
protected:
	Character() : Name("EMPTYCHARACTER"), Species(VOIDWALKER), type(STORY) {}
public:
	Character(string name, SpeciesType species, CharacterType Character_Type) : Name(name), Species(species), type(Character_Type) {}
	string get_name();
	SpeciesType get_species();
	CharacterType get_type();
};
// When a function looks for a specific character and doesn't find it, it should return nullCharacter to indicate the character was not found.
#ifndef NULLCHARACTER
#define NULLCHARACTER
static Character nullCharacter("NULLCHARACTER", VOIDWALKER, STORY);
#endif