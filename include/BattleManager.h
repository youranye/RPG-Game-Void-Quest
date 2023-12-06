#ifndef BATTLEMANAGER_H
#define BATTLEMANAGER_H

#include "Character.h"
#include "Player.h"
#include "IOManager.h"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <stdexcept>

// Describes result of the battle
enum BattleOutcome { WIN, DEATH, ONGOING };

class BattleManager
{
    public:
        BattleManager(Player* playerCharacter, Character& enemyCharacter, IOManager& ioManager)
            : player(playerCharacter), enemy(enemyCharacter), result(ONGOING), ioManager(ioManager)
        {
            if(player == nullptr || enemyCharacter == nullCharacter)
            {
                throw std::invalid_argument("Invalid BattleManager constructor.");
            }
            playerAbility = player->getAbility();
            enemyAbility = enemy.getAbility();
        }
        void runBattle();
        BattleOutcome getBattleOutcome();
        //Protected for easier testing
    protected:
        Player* player;
        Character& enemy;
        BattleOutcome result;
        IOManager& ioManager;
        Ability playerAbility;
        Ability enemyAbility;

        virtual int chooseAction();
        void attack(bool isPlayerAttacker);
        virtual void specialAttack(bool isPlayer); //virtual because if someone wanted to do special attacks differently they can override this.
        void heal(bool isPlayer);
        virtual int randNumGenerator(int lowest, int highest); //virtual since it is random, and to test this code, easy to override.
        virtual int determineAttackSuccess(int accuracy, int dodge); //virtual if someone wanted to override the success rate of a attack
        int calculateDamage(int attackPower, int attackMod, int targetDefense, int defenseMod, int hitValue);
        void displayAttack(bool isSpecial, bool isPlayer, int success, int damage);
        void displayHeal(bool isPlayer, int amount);
};

#endif //BATTLEMANAGER_H