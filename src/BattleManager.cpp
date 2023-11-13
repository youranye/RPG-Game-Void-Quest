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
    while (player.getHP() >= 0 && enemy.getHP() >= 0)
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
    // TODO: implement FLEE result    
}

// Returns outcome of the battle.
BattleOutcome BattleManager::getBattleOutcome() { return result; }

// TODO: User chooses their action. Options are any of their attacks or fleeing.
void BattleManager::chooseAction() {}

/* Given an attacker and a target, calculates the results of an attack, deals appropriate damage to target,
   and displays results of the attack to the user. */
void BattleManager::attack(Character& attacker, Character& target)
{
    srand(time(nullptr));

    int accuracy = (rand() % 100) + 1;
    int dodge = target.getDexterity();
    int attackModifier = (rand() % 10) + 1;
    int defenseModifier = (rand() % 10) + 1;
    int hitValue = -1;
    int attackPower = attacker.getAttack();
    int targetDefense = target.getDefense();
    int totalDamage = 0;

    // Determine whether the attack hits
    if (accuracy < dodge)
    {
        hitValue = 0; // miss
    }
    else if (accuracy > (100 - dodge))
    {
        hitValue = 2; // critical hit, double damage
    } 
    else
    {
        hitValue = 1; // hit, normal damage
    }

    // Determine amount of damage the target takes
    totalDamage = ((attackPower * attackModifier) - (targetDefense * defenseModifier)) * hitValue * 0.3;

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

// Return true if the attack hits and false if the attack misses based on the successValue.
bool BattleManager::determineAttackSuccess(int successValue)
{
    if (successValue <= 0)
    { 
        return false;
    }
    else
    {
        return true;
    }
}

// TODO: Display the results of the attack to the user.
void BattleManager::displayAttack(const Character& attacker, const Character& target, int success, int damage)
{}

// TODO: necessary to run code, put in test file soon
int main()
{
    Character rogue(15,90,12,11,20);
    Character paladin(25,60,9,15,10);
    BattleManager testBattle(rogue, paladin);

    testBattle.runBattle();
    BattleOutcome result = testBattle.getBattleOutcome();

    if (result == WIN)
    {
        std::cout << "win\n";
    }
    else if (result == DEATH)
    {
        std::cout << "death\n";
    }
    else
    {
        std::cout << "undetermined\n";
    }

    return 0;
}