#include "SceneManager.h"
#include <cassert>
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

void SceneManager::handleNonBattleScene(NarrativeScene* nScene) 
{
    ioManager.write(nScene->getText());
    ioManager.write("\n");
    std::vector<std::string> options = nScene->getOptions();
    std::stringstream ss;
    ss << "Options: " << "\n";
    for(int i = 0; i < options.size(); i++)
    {
        char letter = 'a' + i;
        ss << letter << ") " << options.at(i) << "\n";
    }
    ioManager.write(ss.str());
    int userOption = ioManager.readOption(options.size()); 
    //Based on userChoice, transition to the next scene
    goToNextScene(nScene->getNextKey(userOption));
}

void SceneManager::handleBattleScene(BattleScene* bScene) 
{
    std::string enemyKey = bScene->getEnemyName();
    Character& enemy = characterManager.getCharacter(enemyKey);

    if (enemy == nullCharacter) 
    {
        ioManager.write("Error: Enemy not found.\n");
        ioManager.write("Skipping Fight\n");
        goToNextScene(bScene->getNextKey());
        return;
    }

    ioManager.write("Battle begins with enemy: " + enemyKey);
    // Run the battle with the obtained enemy using BattleManager
    Player* player = characterManager.getPlayer();
    if(player == nullptr)
    {
        ioManager.write("hmm, it seems you haven't told me your name yet.\n");
        ioManager.write("Now, would you tell me who you are?\n");
        characterManager.initialize();
        player = characterManager.getPlayer();
    }
    assert(player != nullptr); // TODO: handle this error
    BattleManager battleManager(player, enemy, ioManager);
    if(enemy.getType() == BOSS)
    {
        ioManager.write("\nYour HP and SP have Been Restored!");
    }
    ioManager.write("\n");
    battleManager.runBattle();
    BattleOutcome battleOutcome = battleManager.getBattleOutcome();
    string nextSceneKey = bScene->getNextKey();

    if (battleOutcome == WIN) 
    {
        ioManager.write("You won the battle!\n");
    } else 
    {
        ioManager.write("You lost the battle!\n");
        ioManager.write("Game Over!\n");
        nextSceneKey = "start#end";
    }

    goToNextScene(nextSceneKey);
}

bool SceneManager::isFinalSceneReached(string sceneKey = "")
{
    if (currentScene == nullptr)
    {
        ioManager.write("Error: Current scene not found.\n");
        return false;
    }
    if(!sceneKey.empty())
    {
        if(sceneKey == "start#end")
        {
            return true;
        } else
        {
            return false;
        }
    }

    BattleScene* bScene = dynamic_cast<BattleScene*>(currentScene);
    NarrativeScene* nScene = dynamic_cast<NarrativeScene*>(currentScene);
    
    if (bScene != nullptr)
    {
        if(bScene->getNextKey() == "start#end")
        {
            return true;
        }
    }
    else
    {
        std::vector<std::string> options = nScene->getOptions();
        for(int i = 0; i < options.size(); i++)
        {
            if(nScene->getNextKey(i) == "start#end")
            {
                return true;
            }
        }
    }
    return false;
}

void SceneManager::goToNextScene(const std::string& nextSceneKey)
{
    if(isFinalSceneReached(nextSceneKey))
    {
        return;
    }
    replaceScene(nextSceneKey);
    runScene();
}
