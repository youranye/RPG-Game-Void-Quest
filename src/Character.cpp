#include "Character.h"

string Character::get_name() const
{
	return Name;
}

SpeciesType Character::get_species() const
{
	return Species;
}

CharacterType Character::get_type() const
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

bool Character::operator==(const Character &rhs) const
{
    if(rhs.get_name()==this->Name && rhs.get_species() == this->Species && rhs.get_type() == this->type)
    {
        return true;
    }
    return false;
}

const int Character::get_max_hp()
{
    return maxHP;
}

Ability Character::get_ability()
{
    return ability;
}

string Character::getHpBar()
{
    return "";
}