#include "Character.h"

string Character::get_name()
{
	return Name;
}

SpeciesType Character::get_species()
{
	return Species;
}

CharacterType Character::get_type()
{
	return type;
}

int Character::get_attack()
{
    return attack;
}

int Character::get_defense()
{
    return defense;
}

int Character::get_dexterity()
{
    return dexterity;
}

int Character::get_hp()
{
    return hp;
}

void Character::heal(int amount)
{
    if (hp < maxHP)
    {
        hp += amount;
    }
    if(hp > maxHP)
    {
        hp = maxHP;
    }
}

void Character::take_damage(int amount)
{
    hp -= amount;
    if (hp < 0)
    {
        hp = 0;
    }
}