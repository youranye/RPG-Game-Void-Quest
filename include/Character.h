#pragma once
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

//character and enemy shared enums
enum SpeciesType {HUMAN, ELF, DWARF, GOBLIN, TABAXI, ORC, GOLIATH, CHANGELING, GNOME, VOIDWALKER};
//utilize to differentiate between player type character and Enemy type character
enum CharacterType {PLAYER, ENEMY, STORY, BOSS};

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
	const int maxHP;
	int attack;
	int defense;
	int dexterity;
	int hp;
	vector<Ability> abilities;
	Ability ability;
	Character() : Name("EMPTYCHARACTER"), Species(VOIDWALKER), type(STORY), maxHP(0), ability(Ability()) {}
public:
	Character(string name, SpeciesType species, CharacterType Character_Type, int health) : 
	Name(name), Species(species), type(Character_Type), maxHP(health), attack(0), defense(0), dexterity(0), hp(health), ability(Ability()) 
	{
		if(name.empty())
		{
			throw std::invalid_argument("name cannot be empty");
		}
		if(health <= 0)
		{
			throw std::invalid_argument("health cannot be less than or equal to zero");
		}
	}
	Character(string name, SpeciesType species, CharacterType Character_Type, int health, int atk, int def, int dex) : Name(name), Species(species), type(Character_Type), maxHP(health), attack(atk), defense(def), dexterity(dex), hp(health) 
	{
		if(name.empty())
		{
			throw std::invalid_argument("name cannot be empty");
		}
		if(health <= 0)
		{
			throw std::invalid_argument("health cannot be less than or equal to zero");
		}
	}
	string get_name() const;
	SpeciesType get_species() const;
	CharacterType get_type() const;
	int get_attack();
	int get_defense();
	int get_dexterity();
	int get_hp();
	const int get_max_hp();
	void heal(int amount);
	void take_damage(int amount);
	bool operator==(const Character& rhs) const;
	Ability get_ability();
	string getHpBar();
};
// When a function looks for a specific character and doesn't find it, it should return nullCharacter to indicate the character was not found.
#ifndef NULLCHARACTER
#define NULLCHARACTER
static Character nullCharacter("NULLCHARACTER", VOIDWALKER, STORY, 1, 0, 0, 0);
#endif
