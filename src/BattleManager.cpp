#include "../include/BattleManager.h"

// Runs the battle using turn-based combat
void BattleManager::runBattle()
{
    // If enemy has higher dexterity than the player, they attack first.
    if (enemy.get_dexterity() > player->get_dexterity())
    {
        attack(false);
    }

    // Player and enemy take turns attacking each other until one is dead or the player flees.
    while (player->get_hp() > 0 && enemy.get_hp() > 0)
    {
        bool playerChoiceValid = false;
        while(!playerChoiceValid)
        {
            switch(chooseAction())
            {
                case 1:
                    attack(true);
                    playerChoiceValid = true;
                    break;
                case 2:
                    if(player->get_sp() < 5)
                    {
                        //cout not enough sp
                        ioManager.write("Not Enough SP to case Heal!\n");
                    }
                    else
                    {
                        heal(true);
                        playerChoiceValid = true;
                    }
                    break;
                case 3:
                    if(player->get_sp() < 5)
                    {
                        //cout not enough sp
                        ioManager.write("Not Enough SP to use Special Attack!\n");
                    }
                    else
                    {
                        specialAttack(true);
                        playerChoiceValid = true;
                    }
                    break;
            }
        }

        if (enemy.get_hp() >= 0)
        {
            int desiretoheal = 0;
            if(enemy.get_hp() < enemy.get_max_hp())
            {
                int desiretoheal = randNumGenerator(0, enemy.get_max_hp());
            }
            if(enemy.get_hp() < desiretoheal)
            {
                heal(false);
            }
            else if(enemy.get_hp() < 5)
            {
                specialAttack(false);
            }
            else
            {
                attack(false);
            }
        }
    }

    // Change result to the outcome of the battle
    if (player->get_hp() <= 0)
    {
        result = DEATH;
    }
    else 
    {
        result = WIN;
    }
}

// Returns outcome of the battle.
BattleOutcome BattleManager::getBattleOutcome() 
{ 
    return result; 
}

// user chooses action
int BattleManager::chooseAction()
{
    std::stringstream ss;
    ss << "Enemy Health: " << enemy.get_hp() << "/" << enemy.get_max_hp() << "\n" <<
        "Player Health: " << player->get_hp() << "/" << player->get_max_hp() << "\n" <<
        "Player SP: " << player->get_sp() << "/" << player->get_max_sp() << "\n" <<
        "Options: " << "\n" <<
        "a) attack Cost: 0" << "\n" <<
        "b) heal Cost: 5 SP" << "\n" <<
        "c) special attack" << " Cost: " << "5" << " SP" << std::endl;
    ioManager.write(ss.str());
    return ioManager.readOption(3);
}

/* Given an attacker and a target, calculates the results of an attack, deals appropriate damage,
   and displays results of the attack to the user. */
void BattleManager::attack(bool isPlayerAttacker)
{
    
    int accuracy = randNumGenerator(1,100);
    int dodge = 0;
    int atkMod = randNumGenerator(1,10);
    int defMod = randNumGenerator(1,10);
    int atkPower = 0;
    int targetDefense = 0;

    if(isPlayerAttacker)
    {
        dodge = enemy.get_dexterity();
        atkPower = player->get_attack();
        targetDefense = enemy.get_defense();
    }
    else
    {
        dodge = player->get_dexterity();
        atkPower = enemy.get_attack();
        targetDefense = player->get_defense();
    }
    // Determine whether the attack hits
    int hitValue = determineAttackSuccess(accuracy, dodge);
    if(isPlayerAttacker && hitValue == 2)
    {
        player->regenerate_sp(100);
        //display to player
    }

    // Calculate amount of damage the target takes
    int totalDamage = calculateDamage(atkMod, atkPower, defMod, targetDefense, hitValue);

    // If totalDamage is negative, the target takes 0 damage
    if (totalDamage < 0)
    {
        totalDamage = 0;
    }
    else
    {
        if(isPlayerAttacker)
        {
            enemy.take_damage(totalDamage);
        }
        else
        {
            player->take_damage(totalDamage);
        }
    }

    // Display result of attack to user
    displayAttack(isPlayerAttacker, hitValue, totalDamage);
}

// Generates random integer with range from lowest to highest inclusive
int BattleManager::randNumGenerator(int lowest, int highest)
{
    srand(time(nullptr));

    int range = highest - lowest + 1;
    return (rand() % range) + lowest;
}

void BattleManager::specialAttack(bool isPlayer)
{

}

// heals 10 hp
void BattleManager::heal(bool isPlayer)
{
    int amount = 10;
    if(isPlayer)
    {
        if(player->get_sp() < 5)
        {
            //somehow tell player not enough sp
        } else
        {
            player->spend_sp(5);
            int initialHP = player->get_hp();
            player->heal(amount);
            amount = player->get_hp() - initialHP;
        }
    } else
    {
        int initialHP = enemy.get_hp();
        enemy.heal(amount);
        amount = enemy.get_hp() - initialHP;
    }
    displayHeal(isPlayer,amount);
}

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
void BattleManager::displayAttack(bool isPlayer, int success, int damage)
{
    std::stringstream ss;
    if(isPlayer)
    {
        switch(player->get_class())
        {
            case FORGED:
                switch(success)
                {
                    case 0:
                        ss << "You try to swing your axe at " << enemy.get_name() << 
                            " and your axe flies right out of your hand\n";
                        break;
                    case 1:
                        ss << "You swing your axe down on " << enemy.get_name() << 
                            " and your axe deals " << damage << " damage to " << enemy.get_name() << std::endl;
                        break;
                    case 2:
                        ss << "Critical Hit!\n" <<
                            "You Hurl your axe at " << enemy.get_name() << 
                            " and your axe deals " << damage << " damage to " << enemy.get_name() << "\n";
                        break;
                }
                break;
            case WARLOCK:
                switch(success)
                {
                    case 0:
                        ss << "You try to hit " << enemy.get_name() << 
                            " with your staff and you miss completely\n";
                        break;
                    case 1:
                        ss << "You bash " << enemy.get_name() << 
                            " with your staff and deal " << damage << " damage to " << enemy.get_name() << std::endl;
                        break;
                    case 2:
                        ss << "Critical Hit!\n" <<
                            "You try to bash " << enemy.get_name() << 
                            " with your staff and cast a fireball dealing " << damage << " damage to " << enemy.get_name() << std::endl;
                        break;
                }
                break;
            case ROGUE:
                switch(success)
                {
                    case 0:
                        ss << "You try to plunge your dagger into " << enemy.get_name() << 
                            " and you drop your dagger on the ground\n";
                        break;
                    case 1:
                        ss << "You swing your dagger at " << enemy.get_name() << 
                            " and deal " << damage << " damage to " << enemy.get_name() << std::endl;
                        break;
                    case 2:
                        ss << "Critical Hit!\n" <<
                            "You plunge your dagger into " << enemy.get_name() << 
                            " and deal " << damage << " damage to " << enemy.get_name() << std::endl;
                        break;
                }
                break;
            case PALADIN:
                switch(success)
                {
                    case 0:
                        ss << "You try to swing your sword at " << enemy.get_name() << 
                            " and your sword flies right out of your hand\n";
                        break;
                    case 1:
                        ss << "You swing your sword at " << enemy.get_name() << 
                            " and you deal " << damage << " damage to " << enemy.get_name() << std::endl;
                        break;
                    case 2:
                        ss << "Critical Hit!\n" <<
                            "You swing your sword at " << enemy.get_name() << 
                            " and you cast fireball dealing " << damage << " damage to " << enemy.get_name() << std::endl;
                        break;
                }
                break;
        }
    }
    else
    {
        //TODO: put ones for enemies once enemies are written
    }
    ioManager.write(ss.str());
}

// TODO: Helper of heal that displays the results of the heal to the user.
void BattleManager::displayHeal(bool isPlayer, int amount)
{
    std::stringstream ss;
    if(isPlayer)
    {
        ss << "you cast Heal and heal " << amount << " hp!\n";
    }
    else
    {
        ss << enemy.get_name() << " casts Heal and heals " << amount << " hp!\n";
    }
    ioManager.write(ss.str());
}