#include "Enemy.h"

int Enemy::get_attack()
{
    return attack;
}

int Enemy::get_defense()
{
    return defense;
}

int Enemy::get_dexterity()
{
    return dexterity;
}

int Enemy::get_hp()
{
    return hp;
}

void Enemy::heal(int amount)
{
    if (hp < maxHP)
    {
        hp += amount;
    }
    if (hp > maxHP)
    {
        hp = maxHP;
    }
}

void Enemy::take_damage(int amount)
{
    hp -= amount;
    if (hp < 0)
    {
        hp = 0;
    }
}
