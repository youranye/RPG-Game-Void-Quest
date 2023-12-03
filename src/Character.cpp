#include "Character.h"

std::string Character::getName() const
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

int Character::getMaxHP()
{
    return maxHP;
}

Ability Character::getAbility()
{
    return ability;
}

std::string Character::getHPBar()
{
    int bars = hp/5;
    int totalBars = maxHP/5;
    std::string hpColor = "\033[1;32m"; //green
    if(totalBars > 100) //for crazy large health bars
    {
        totalBars = 100;
        bars = hp/(maxHP/100);
    }
    double percentHP = 100.0*(bars/(totalBars*1.0));
    if(percentHP <= 80)
    {
        hpColor = "\033[1;33m"; //yellow
    }
    if(percentHP <= 50)
    {
        hpColor = "\033[38:5:202m"; //orange
    }
    if(percentHP <= 30)
    {
        hpColor = "\033[1;31m"; //red
    }
    std::stringstream ss;
    ss << "[";
    if(hp <= 0)
    {
        for(int i = 0; i < totalBars; i++)
        {
            ss << " ";
        }
    } else
    {
        ss << hpColor;
        bool colored = true;
        for(int i = 0; i < totalBars; i++)
        {
            if(i < bars)
            {
                ss << ":";
            } else
            {
                if(colored)
                {
                    ss << "\033[1;0m";
                    colored = false;
                }
                ss << " ";
            }
        }
        if(colored)
        {
            ss << "\033[1;0m";
            colored = false;
        }
    }
    ss << "]";
    return ss.str();
}