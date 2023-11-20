#include "Character.h"

string Character::getName() const
{
	return Name;
}

SpeciesType Character::getSpecies() const
{
	return Species;
}

CharacterType Character::getType() const
{
	return type;
}

int Character::getAttack()
{
    return attack;
}

int Character::getDefense()
{
    return defense;
}

int Character::getDexterity()
{
    return dexterity;
}

int Character::getHP()
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

void Character::takeDamage(int amount)
{
    hp -= amount;
    if (hp < 0)
    {
        hp = 0;
    }
}

bool Character::operator==(const Character &rhs) const
{
    if(rhs.getName()==this->Name && rhs.getSpecies() == this->Species && rhs.getType() == this->type)
    {
        return true;
    }
    return false;
}
