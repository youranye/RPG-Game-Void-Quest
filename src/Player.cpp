#include "Player.h"

Player::Player(string name, SpeciesType species, CharacterType Character_Type, ClassType class_type, Religion Religion_, int health, int maxsp) :
    Character(name, species, Character_Type), Class_Type(class_type), religion(Religion_), attack(0), defense(0), dexterity(0), hp(health), sp(maxsp), maxHP(health), maxSP(maxsp), level(1)
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
        //class ability
        abilities.push_back(Ability("Throw Dagger", ATTACK, "Throw dagger at enemy", NONE, 120, 6, 99));
        break;
    case PALADIN:
        attack = 9;
        defense = 15;
        dexterity = 10;
        //class ability depends on religion
        switch (religion)
        {
        case TRAVELER:

            break;
        case SHADOW:

            break;
        case NOTHING:

            break;
        case SILVER:

            break;
        case FORGE:
            //(Planned) throw some kind of exception
            break;
        }
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

int Player::get_attack()
{
    return attack;
}

int Player::get_defense()
{
    return defense;
}

int Player::get_dexterity()
{
    return dexterity;
}

int Player::get_hp()
{
    return hp;
}

void Player::heal(int amount)
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

void Player::take_damage(int amount)
{
    hp -= amount;
    if (hp < 0)
    {
        hp = 0;
    }
}

//Not yet complete will complete once Story is closer to being finished writing
Ability Player::levelup()
{
    level++;
    hp = maxHP;
    sp = maxSP;
    attack++;
    defense++;
    dexterity++;
    Ability newAbility;
    switch (level) {
    case 2:

        break;
    case 3:

        break;
    case 4:

        break;
    case 5:

        break;
    }
    abilities.push_back(newAbility);
    return newAbility;
}
