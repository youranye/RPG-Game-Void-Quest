#ifndef BATTLEMANAGER_H
#define BATTLEMANAGER_H

#include "../include/Character.h"

// Describes result of the battle
enum BattleOutcome { WIN, DEATH, ONGOING };

class BattleManager
{
    public:
        BattleManager(Character& playerCharacter, Character& enemyCharacter)
            : player(playerCharacter), enemy(enemyCharacter), result(ONGOING)
        {}
        void runBattle();
        BattleOutcome getBattleOutcome();

    private:
        Character& player;
        Character& enemy;
        BattleOutcome result;

        void chooseAction();
        void attack(Character& attacker, Character& target);
        void heal(Character& self);
        int randNumGenerator(int lowest, int highest);
        int determineAttackSuccess(int accuracy, int dodge);
        int calculateDamage(int attackPower, int attackMod, int targetDefense, int defenseMod, int hitValue);
        void displayAttack(const Character& attacker, const Character& target, int success, int damage);
        void displayHeal(const Character& self, int amount);
};

#endif //BATTLEMANAGER_H