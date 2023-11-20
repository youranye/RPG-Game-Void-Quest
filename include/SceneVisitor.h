#ifndef SCENEVISITOR_H
#define SCENEVISITOR_H

class NarrativeScene;
class BattleScene;

class SceneVisitor
{
  public:
    virtual void visit(NarrativeScene &scene) = 0;
    virtual void visit(BattleScene &scene) = 0;
};

#endif