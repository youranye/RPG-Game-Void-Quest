#include "../include/BattleManager.h"

// Runs the battle using turn-based combat
void BattleManager::battle() {}

// User chooses their action. Any attack, or fleeing. Implement later using IOManager.
void BattleManager::chooseAction() {}

// Return true if the attack hits and false if the attack misses.
bool BattleManager::determineAttackSuccess() { return false; }

// Calculates damage and reduces hitpoints of the damaged character.
void BattleManager::dealDamage() {}

// Tells the user the outcome of an attack. Implement later using IOManager.
void BattleManager::displayAttack() {}

// Returns outcome of the battle.
BattleOutcome BattleManager::getBattleOutcome() { return result; }

// necessary to run code, put in test file soon
int main() {
    return 0;
}