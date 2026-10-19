#pragma once

#include "SceneBase.h"
#include "../Actor/Actor.h"

#include <memory>

class GameScene : public SceneBase
{
public:
    bool Load() override;
    void Initialize() override;
    void Execute() override;
    SceneType Terminate() override;
    //void Draw() override;

private:
    std::unique_ptr<Actor> skyboxObject;
    std::unique_ptr<Actor> uiObject;
};
