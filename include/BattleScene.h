#pragma once
#ifndef BATTLESCENE_H
#define BATTLESCENE_H

#include "Player.h"
#include "Scene.h"

class BattleScene : public Scene
{
  private:
    std::string enemyName;
    std::string nextKey;

  public:
    BattleScene(std::string const &enemyName, std::string const &nextKey) : enemyName{enemyName}, nextKey{nextKey}
    {
    }

    virtual std::string getText() const override
    {
        // TODO: Actually add the battle information
        return "Fighting: " + enemyName;
    };

    virtual std::vector<std::string> getOptions() const override
    {
        return {"Attack", "Flee"};
    }

    /// @brief Get the name of the enemy in the battle
    /// @return The name of the enemy
    std::string getEnemyName() const
    {
        return enemyName;
    }

    /// @brief Get the key of the scene to go to after the battle
    /// @return The key of the next scene
    std::string getNextKey() const
    {
        return nextKey;
    }
};

#endif