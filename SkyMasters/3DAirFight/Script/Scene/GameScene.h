#pragma once

#include "SceneBase.h"
#include "../Actor/Actor.h"
#include"../Game/Game.h"

#include <memory>

class GameScene : public SceneBase
{
public:
    GameScene(SceneManager* sceneManager) : SceneBase(sceneManager) {};

    bool Load() override;
    void Initialize() override;
    void Execute() override;
    SceneType Terminate() override;

private:
    class Game* mGame;

    std::unique_ptr<Actor> skyboxObject;
    std::unique_ptr<Actor> uiObject;
};
