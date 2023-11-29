#include "SceneManager.h"

void SceneManager::runScene()
{
    if (currentScene == nullptr)
    {
        ioManager.write("Error: Current scene not found.\n");
        return;
    }

    BattleScene* bScene = dynamic_cast<BattleScene*>(currentScene);
    NarrativeScene* nScene = dynamic_cast<NarrativeScene*>(currentScene);

    if (bScene != nullptr)
    {
        handleBattleScene(bScene);
    }
    else
    {
        handleNonBattleScene(nScene);
    }
}

void SceneManager::replaceScene(std::string const &key)
{
    currentScene = &(store->getScene(key));
}

void SceneManager::handleNonBattleScene(NarrativeScene* nScene) {
    ioManager.write(nScene->getText());
    std::vector<std::string> options = nScene->getOptions();
    int userOption = ioManager.readOption(options.size()); 
    //Based on userChoice, transition to the next scene
    replaceScene(nScene->getNextKey(userOption));
}

void SceneManager::handleBattleScene(BattleScene* bScene) {
    //std::string enemyKey = currentScene->getEnemyName();
    // Character* enemy = &characterManager.getCharacter(enemyKey);

    // if (enemy == nullptr) {
    //     ioManager.write("Error: Enemy not found.\n");
    //     return;
    // }

    // ioManager.write("Battle begins with enemy: " + enemyKey);

    // // Run the battle with the obtained enemy using BattleManager
    // Player* player = characterManager.getPlayer();
    // BattleManager battleManager(player, *enemy, ioManager);
    // battleManager.runBattle();
    // BattleOutcome battleOutcome = battleManager.getBattleOutcome();

    // if (battleOutcome == WIN) {
    //     ioManager.write("You won the battle!\n");
    // } else {
    //     ioManager.write("You lost the battle!\n");
    // }

    // replaceScene(currentScene->getNextKey());
}
