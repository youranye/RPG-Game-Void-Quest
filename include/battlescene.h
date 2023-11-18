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
    BattleScene(std::string enemyName) : enemy{enemyName}
    {
    }

    void accept(SceneVisitor &visitor)
    {
        visitor.visit(*this);
    }
};

#endif