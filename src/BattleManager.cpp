#include "../include/BattleManager.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

// Runs the battle using turn-based combat
void BattleManager::runBattle()
{
    // If enemy has higher dexterity than the player, they attack first.
    if (enemy.getDexterity() > player.getDexterity())
    {
        attack(enemy, player);
    }

    // Player and enemy take turns attacking each other until one is dead or the player flees.
    while (player.getHP() > 0 && enemy.getHP() > 0)
    {
        // TODO: give player a choice
        // TODO: implement flee option
        attack(player, enemy);

        if (enemy.getHP() >= 0)
        {
            attack(enemy, player);
        }
    }

    // Change result to the outcome of the battle
    if (player.getHP() <= 0)
    {
        result = DEATH;
    }
    else {
        result = WIN;
    }  
}

// Returns outcome of the battle.
BattleOutcome BattleManager::getBattleOutcome() { return result; }

// TODO: User chooses their action, either attack or heal.
void BattleManager::chooseAction()
{}

/* Given an attacker and a target, calculates the results of an attack, deals appropriate damage,
   and displays results of the attack to the user. */
void BattleManager::attack(Character& attacker, Character& target)
{
    int accuracy = randNumGenerator(1,100);
    int dodge = target.getDexterity();
    int atkMod = randNumGenerator(1,10);
    int defMod = randNumGenerator(1,10);
    int atkPower = attacker.getAttack();
    int targetDefense = target.getDefense();

    // Determine whether the attack hits
    int hitValue = determineAttackSuccess(accuracy, dodge);

    // Calculate amount of damage the target takes
    int totalDamage = calculateDamage(atkMod, atkPower, defMod, targetDefense, hitValue);

    // If totalDamage is negative, the target takes 0 damage
    if (totalDamage < 0)
    {
        totalDamage = 0;
    }
    else{
        target.takeDamage(totalDamage);
    }

    // Display result of attack to user
    displayAttack(attacker, target, hitValue, totalDamage);
}

// Generates random integer with range from lowest to highest inclusive
int BattleManager::randNumGenerator(int lowest, int highest)
{
    srand(time(nullptr));

    int range = highest - lowest + 1;
    return (rand() % range) + lowest;
}

// TODO: Given a target, increases their hitpoints by an amout that depends on their sp.
void BattleManager::heal(Character& self)
{}

// Determine if the attack hits. Returns 0 for miss, 1 for hit, 2 for critical hit
int BattleManager::determineAttackSuccess(int accuracy, int dodge)
{
    if (accuracy < dodge)
    {
        return 0; // miss
    }
    else if (accuracy > (100 - dodge))
    {
        return 2; // critical hit, double damage
    } 
    else
    {
        return 1; // hit, normal damage
    }
}

int BattleManager::calculateDamage(int attackPower, int attackMod, int targetDefense, int defenseMod, int hitValue)
{
    return ((attackPower * attackMod) - (targetDefense * defenseMod)) * hitValue * 0.3;
}
// TODO: Helper of attack that displays the results of the attack to the user.
void BattleManager::displayAttack(const Character& attacker, const Character& target, int success, int damage)
{}

// TODO: Helper of heal that displays the results of the heal to the user.
void BattleManager::displayHeal(const Character& self, int amount)
{}