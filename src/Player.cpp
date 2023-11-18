#include "Player.h"

Player::Player(string name, SpeciesType species, CharacterType Character_Type, ClassType class_type, int health, int maxsp) :
    Character(name, species, Character_Type, health), Class_Type(class_type), sp(maxsp), maxSP(maxsp)
{
    //set abilities and stats
    //not all abilities have yet been implemented will need story to be closer to finished before complete implementation
    abilities.push_back(Ability("Basic Attack", ATTACK, "Hit enemy", NONE, 90, 0, 99));
    abilities.push_back(Ability("Fireball", ATTACK, "Hit enemy with fireball", NONE, 100, 5, 99));
    abilities.push_back(Ability("Heal", HEAL, "Heal", NONE, 10, 10, 100));
    switch (class_type)
    {
    case ROGUE:
        attack = 10;
        defense = 10;
        dexterity = 20;
        break;
    case PALADIN:
        attack = 9;
        defense = 15;
        dexterity = 10;
        break;
    case WARLOCK:
        attack = 9;
        defense = 11;
        dexterity = 15;
        break;
    case FORGED:
        attack = 15;
        defense = 15;
        dexterity = 10;
        break;
    }

}

ClassType Player::get_class()
{
    return Class_Type;
}

int Player::get_sp()
{
    return sp;
}

void Player::spend_sp(int amount)
{
    if (sp < maxSP)
    {
        sp += amount;
    }
    if(sp > maxSP)
    {
        sp = maxSP;
    }
}

void Player::regenerate_sp(int amount)
{
    sp -= amount;
    if (sp < 0)
    {
        sp = 0;
    }
}

const int Player::get_max_sp()
{
    return maxSP;
}
