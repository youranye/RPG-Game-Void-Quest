#pragma once
#ifndef BATTLESCENE_H
#define BATTLESCENE_H

#include "Enemy.h"
#include "Player.h"
#include "scene.h"

class BattleScene : public Scene
{
  private:
    std::string enemyName;

  public:
    BattleScene(std::string enemyName) : enemyName{enemyName}
    {
    }

    void accept(SceneVisitor &visitor) override
    {
        visitor.visit(*this);
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
};

#endif