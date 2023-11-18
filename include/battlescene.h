#pragma once
#ifndef BATTLESCENE_H
#define BATTLESCENE_H

#include "Enemy.h"
#include "Player.h"
#include "scene.h"

class BattleScene : public Scene
{
  private:
    Player &player;
    Enemy &enemy;

  public:
    BattleScene(Player &player, Enemy &enemy) : player{player}, enemy{enemy}
    {
    }

    void accept(SceneVisitor &visitor)
    {
        visitor.visit(*this);
    }
};

#endif