#ifndef BATTLEMANAGER_H
#define BATTLEMANAGER_H

#include "Character.h"
#include "Player.h"
#include "IOManager.h"
#include <cstdlib>
#include <ctime>
#include <sstream>

// Describes result of the battle
enum BattleOutcome { WIN, DEATH, ONGOING };

class BattleManager
{
    public:
        BattleManager(Player* playerCharacter, Character& enemyCharacter, IOManager& ioManager)
            : player(playerCharacter), enemy(enemyCharacter), result(ONGOING), ioManager(ioManager)
        {
            playerAbility = player->getAbility();
            enemyAbility = enemy.getAbility();
        }
        void runBattle();
        BattleOutcome getBattleOutcome();

    private:
        Player* player;
        Character& enemy;
        BattleOutcome result;
        IOManager& ioManager;
        Ability playerAbility;
        Ability enemyAbility;

        int chooseAction();
        void attack(bool isPlayerAttacker);
        void specialAttack(bool isPlayer);
        void heal(bool isPlayer);
        int randNumGenerator(int lowest, int highest);
        int determineAttackSuccess(int accuracy, int dodge);
        int calculateDamage(int attackPower, int attackMod, int targetDefense, int defenseMod, int hitValue);
        void displayAttack(bool isSpecial, bool isPlayer, int success, int damage);
        void displayHeal(bool isPlayer, int amount);
};

#endif //BATTLEMANAGER_H