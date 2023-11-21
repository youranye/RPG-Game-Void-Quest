#include "Player.h"

Player::Player(string name, SpeciesType species, ClassType class_type, int health, int maxsp) :
    Character(name, species, PLAYER, health), Class_Type(class_type), sp(maxsp), maxSP(maxsp)
{
    if(health <= 0 || maxsp < 0)
    {
        throw std::invalid_argument("health and maxsp cannot be negative or zero!");
    }
    //set abilities and stats
    
    switch (class_type)
    {
    case ROGUE:
        ability = Ability("Sneak Attack", ATTACK, "You call upon The power of the Shadow and stab your foe in the Back", NONE, 200, 10);
        attack = 25;
        defense = 15;
        dexterity = 20;
        break;
    case PALADIN:
        ability = Ability("Atk Up", ATTACK, "You raise your sword and call upon the power of the Traveler and you feel power course through your veins as you cut down your enemy", NONE, 150, 7);
        attack = 20;
        defense = 25;
        dexterity = 15;
        break;
    case WARLOCK:
        ability = Ability("FireBall", ATTACK, "You raise your staff and cast fireball", NONE, 150, 8);
        attack = 15;
        defense = 20;
        dexterity = 25;
        break;
    case FORGED:
        ability = Ability("Atk Down", DEBUFF, "You call upon Huldra and she weakens the strength of your foe and you swing your axe", DEF, 75, 5);
        attack = 30;
        defense = 30;
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
    sp -= amount;
    if (sp < 0)
    {
        sp = 0;
    }
}

void Player::regenerate_sp(int amount)
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

const int Player::get_max_sp()
{
    return maxSP;
}
