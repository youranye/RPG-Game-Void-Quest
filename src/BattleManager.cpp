#include "BattleManager.h"
#include <cmath>
// Runs the battle using turn-based combat
void BattleManager::runBattle()
{
    if(enemy.getType() == BOSS)
    {
        //since enemy is a boss player has stats restored.
        int healed = player->getMaxHP()-player->getHP();
        player->heal(1000);
        player->regenerateSP(1000);
        displayHeal(true,healed);
    }
    // If enemy has higher dexterity than the player, they attack first.
    if (enemy.getDexterity() > player->getDexterity())
    {
        attack(false);
    }

    // Player and enemy take turns attacking each other until one is dead or the player flees.
    while (player->getHP() > 0 && enemy.getHP() > 0)
    {
        int userChoice = chooseAction();
        switch(userChoice)
        {
            case 0:
                attack(true);
                break;
            case 1:
                heal(true);
                break;
            case 2:
                specialAttack(true);
        }

        if(enemy.getHP()==0)
        {
            break;
        }

        if (enemy.getHP() > 0)
        {
            int desiretoheal = 0;
            int enemyDesireCost = enemy.getMaxHP() - enemy.getHP();
            
            desiretoheal = randNumGenerator(enemyDesireCost, enemy.getMaxHP());
            if(enemy.getHP() < desiretoheal && enemy.getHP() < 100)
            {
                heal(false);
            }
            else if( ( ( enemy.getHP() - desiretoheal ) > enemyAbility.cost ) && (enemy.getAbility().type != NULLABILITY) )
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
    if (player->getHP() <= 0)
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
    bool playerChoiceValid = false;
    int userChoice = 0;
    while(!playerChoiceValid)
    { 
        // Prompt the user with their action choices
        std::stringstream ss;
        ss << "Enemy Health: " << enemy.getHP() << "/" << enemy.getMaxHP() << " " << enemy.getHPBar() << "\n" <<
            "Player Health: " << player->getHP() << "/" << player->getMaxHP() << " " << player->getHPBar() << "\n" <<
            "Player SP: " << player->getSP() << "/" << player->getMaxSP() << "\n" <<
            "Options: " << "\n" <<
            "a) attack Cost: 0 SP" << "\n" <<
            "b) heal Cost: 5 SP" << "\n" <<
            "c) " << playerAbility.name << " Cost: " << playerAbility.cost << " SP" << "\n";
        ioManager.write(ss.str());
        userChoice = ioManager.readOption(3);

        // Validate the user's choice
        switch(userChoice)
        {
            case 0:
                playerChoiceValid = true;
                break;
            case 1:
                if(player->getSP() < 5)
                {
                    //cout not enough sp
                    ioManager.write("Not Enough SP to case Heal!\n");
                }
                else
                {
                    playerChoiceValid = true;
                }
                break;
            case 2:
                if(player->getSP() < playerAbility.cost)
                {
                    //cout not enough sp
                    ioManager.write("Not Enough SP to use Special Attack!\n");
                }
                else
                {
                    playerChoiceValid = true;
                }
                break;
        }
    }

    return userChoice;
}

/* Given an attacker and a target, calculates the results of an attack, deals appropriate damage,
   and displays results of the attack to the user. */
void BattleManager::attack(bool isPlayerAttacker)
{
    int accuracy = randNumGenerator(1,100);
    int dodge = 0;
    int atkModMin = 1;
    int atkModMax = 10;
    int atkMod = 1;
    int defMod = 1;
    int defModMin = 0;
    int defModMax = 10;
    int atkPower = 0;
    int targetDefense = 0;

    if(isPlayerAttacker)
    {
        dodge = enemy.getDexterity();
        atkPower = player->getAttack();
        targetDefense = enemy.getDefense();
    }
    else
    {
        dodge = player->getDexterity();
        atkPower = enemy.getAttack();
        targetDefense = player->getDefense();
    }

    // Determine whether the attack hits
    int hitValue = determineAttackSuccess(accuracy, dodge);
    if(isPlayerAttacker && hitValue == 2)
    {
        player->regenerateSP(100);
        player->heal(10);
    }
    if(hitValue == 2)
    {
        if(atkPower < 30)
        {
            atkModMax = 20; //since it is crit it should deal near max damage
            atkModMin = 10;
        } else
        {
            atkModMax = 8;
            atkModMin = 5;
            defModMax = 8;
        }
    } 
    else if(hitValue == 1)
    {
        if(atkPower < targetDefense)
        {
            atkModMax = 15;
            defModMax = 8;
        } 
        else if(atkPower < 30)
        {
            atkModMax = 9;
            defModMax = 11;
        } else if(targetDefense < 30)
        {
            atkModMax = 5;
            defModMax = 15;
        }
    }

    //calculate atkMod
    atkMod = randNumGenerator(atkModMin,atkModMax);
    defMod = randNumGenerator(defModMin,defModMax);
    // Calculate amount of damage the target takes
    int totalDamage = calculateDamage(atkMod, atkPower, defMod, targetDefense, hitValue);

    // If totalDamage is negative, the target takes 0 damage
    if (totalDamage < 0)
    {
        totalDamage = 0;
    }
    if(totalDamage == 0 && hitValue >= 1)
    {
        totalDamage = 5;
    }
    if(isPlayerAttacker)
    {
        enemy.takeDamage(totalDamage);
    }
    else
    {
        player->takeDamage(totalDamage); 
    }

    // Display result of attack to user
    displayAttack(false, isPlayerAttacker, hitValue, totalDamage);
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
    int accuracy = randNumGenerator(15,100);
    int dodge = 0;
    int atkModMin = 1;
    int atkModMax = 10;
    int atkMod = 1;
    int defMod = 1;
    int defModMin = 0;
    int defModMax = 10;
    int atkPower = 0;
    int targetDefense = 0;
    Ability abilityused;

    if(isPlayer)
    {
        player->spendSP(playerAbility.cost);
        dodge = enemy.getDexterity();
        abilityused = playerAbility;
        atkPower = player->getAttack();
        targetDefense = enemy.getDefense();
    }
    else
    {
        dodge = player->getDexterity();
        abilityused = enemyAbility;
        atkPower = enemy.getAttack();
        targetDefense = player->getDefense();
    }
    if(atkPower < targetDefense)
    {
        atkModMax = 15;
        defModMax = 8;
    } 
    else if(atkPower < 30)
    {
        atkModMax = 9;
        defModMax = 11;
    } 
    else if(targetDefense < 30)
    {
        atkModMax = 5;
        defModMax = 15;
    }
    //determine what type of ability is used
    if(abilityused.type == NULLABILITY) //failsafe for characters with no abilities
    {
        attack(isPlayer); //if enemy has no ability or just general error fixing.
        return;
    }
    if(abilityused.type == ATTACK)
    {
        atkPower = std::ceil((atkPower * abilityused.power) / 100.0);
    }
    else
    {
        //debuff
        if(abilityused.condition == DEF)
        {
            targetDefense = std::ceil((targetDefense * (100 - abilityused.power)) / 100.0);
        } else
        {
            dodge = std::ceil((dodge * (100 - abilityused.power)) / 100.0);
        }
    }

    //ability is attack
    // Determine whether the attack hits
    int hitValue = determineAttackSuccess(accuracy, dodge);
    if(isPlayer && hitValue == 2)
    {
        player->regenerateSP(100);
        player->heal(10);
    }
    if(hitValue == 2)
    {
        if(atkPower < 30 || abilityused.type == ATTACK)
        {
            atkModMax = 20; //since it is crit it should deal near max damage
            atkModMin = 10;
        } 
        else
        {
            atkModMax = 8;
            atkModMin = 5;
            defModMax = 8;
        }
    }

    //calculate atkMod
    atkMod = randNumGenerator(atkModMin,atkModMax);
    defMod = randNumGenerator(defModMin,defModMax);
    // Calculate amount of damage the target takes
    int totalDamage = calculateDamage(atkMod, atkPower, defMod, targetDefense, hitValue);

    // If totalDamage is negative, the target takes 0 damage
    if (totalDamage < 0)
    {
        totalDamage = 0;
    }
    if(totalDamage == 0 && hitValue >= 1)
    {
        totalDamage = 5;
    }
    if(isPlayer)
    {
        enemy.takeDamage(totalDamage);
    }
    else
    {
        player->takeDamage(totalDamage);
    }

    // Display result of attack to user
    displayAttack(true, isPlayer, hitValue, totalDamage); 
}

// heals 10 hp
void BattleManager::heal(bool isPlayer)
{
    int amount = 5;
    if(isPlayer)
    {
        player->spendSP(5);
        int initialHP = player->getHP();
        int maxHeal = player->getMaxHP() - initialHP;
        if(initialHP < 10)
        {
            maxHeal = player->getMaxHP() + 30;
            amount = 30;
        }
        if(maxHeal <= 5)
        {
            maxHeal = 10;
        } //prevent floating point error
        amount = randNumGenerator(amount, maxHeal);
        player->heal(amount);
        amount = player->getHP() - initialHP;
    } else
    {
        int initialHP = enemy.getHP();
        if(initialHP <= 5)
        {
            amount = randNumGenerator(5, 20);
        } 
        else if(initialHP <= 50)
        {
            amount = randNumGenerator(5, enemy.getHP());
        } 
        else
        {
            amount = randNumGenerator(5, 50);
        }
        enemy.heal(amount);
        amount = enemy.getHP() - initialHP;
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
void BattleManager::displayAttack(bool isSpecial, bool isPlayer, int success, int damage)
{
    std::stringstream ss;
    if(isSpecial)
    {
        if(isPlayer)
        {
            if(success == 2)
            {
                ss << "Critical Hit!\n";
            }
            ss << playerAbility.description << " dealing " << damage << " damage to " << enemy.getName() << "\n";
        }
        else
        {
            //TODO make it look good
            switch(success)
            {
                case 0:
                    ss << enemy.getName() << " Tries to hit you and misses!\n";
                    break;
                case 1:
                    ss << enemy.getName() << " hits you! Dealing "<< damage << " damage to " << player->getName() << "\n";
                    break;
                case 2:
                    ss << "Critical Hit!\n" <<
                        enemy.getName() << " hits you! Dealing " << damage << " damage to " << player->getName() << "\n";
                    break;
            }
        }
    } 
    else if(isPlayer)
    {
        switch(player->getClass())
        {
            case FORGED:
                switch(success)
                {
                    case 0:
                        ss << "You try to swing your axe at " << enemy.getName() << 
                            " and your axe flies right out of your hand\n";
                        break;
                    case 1:
                        ss << "You swing your axe down on " << enemy.getName() << 
                            " and your axe deals " << damage << " damage to " << enemy.getName() << "\n";
                        break;
                    case 2:
                        ss << "Critical Hit!\n" <<
                            "You Hurl your axe at " << enemy.getName() << 
                            " and your axe deals " << damage << " damage to " << enemy.getName() << "\n";
                        break;
                }
                break;
            case WARLOCK:
                switch(success)
                {
                    case 0:
                        ss << "You try to hit " << enemy.getName() << 
                            " with your staff and you miss completely\n";
                        break;
                    case 1:
                        ss << "You bash " << enemy.getName() << 
                            " with your staff and deal " << damage << " damage to " << enemy.getName() << "\n";
                        break;
                    case 2:
                        ss << "Critical Hit!\n" <<
                            "You try to bash " << enemy.getName() << 
                            " with your staff and cast a fireball dealing " << damage << " damage to " << enemy.getName() << "\n";
                        break;
                }
                break;
            case ROGUE:
                switch(success)
                {
                    case 0:
                        ss << "You try to plunge your dagger into " << enemy.getName() << 
                            " and you drop your dagger on the ground\n";
                        break;
                    case 1:
                        ss << "You swing your dagger at " << enemy.getName() << 
                            " and deal " << damage << " damage to " << enemy.getName() << "\n";
                        break;
                    case 2:
                        ss << "Critical Hit!\n" <<
                            "You plunge your dagger into " << enemy.getName() << 
                            " and deal " << damage << " damage to " << enemy.getName() << "\n";
                        break;
                }
                break;
            case PALADIN:
                switch(success)
                {
                    case 0:
                        ss << "You try to swing your sword at " << enemy.getName() << 
                            " and your sword flies right out of your hand\n";
                        break;
                    case 1:
                        ss << "You swing your sword at " << enemy.getName() << 
                            " and you deal " << damage << " damage to " << enemy.getName() << "\n";
                        break;
                    case 2:
                        ss << "Critical Hit!\n" <<
                            "You swing your sword at " << enemy.getName() << 
                            " and you cast fireball dealing " << damage << " damage to " << enemy.getName() << "\n";
                        break;
                }
                break;
        }
    }
    else
    {
        switch(success)
        {
            case 0:
                ss << enemy.getName() << " Tries to hit you and misses!\n";
                break;
            case 1:
                ss << enemy.getName() << " hits you! Dealing "<< damage << " damage to " << player->getName() << "\n";
                break;
            case 2:
                ss << "Critical Hit!\n" <<
                    enemy.getName() << " hits you! Dealing " << damage << " damage to " << player->getName() << "\n";
                break;
        }
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
        ss << enemy.getName() << " casts Heal and heals " << amount << " hp!\n";
    }
    ioManager.write(ss.str());
}