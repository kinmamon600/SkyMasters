#pragma once

#include "SceneBase.h"
#include "../Actor/Actor.h"
#include"../Game/Game.h"

#include <memory>

class GameScene : public SceneBase
{
public:
<<<<<<< HEAD
    GameScene(SceneManager* sceneManager) : SceneBase(sceneManager) {};
=======
    GameScene(class Game* game);
>>>>>>> bcc4a45b3cb946afa142413c4c781f3eb88fe6cd
    bool Load() override;
    void Initialize() override;
    void Execute() override;
    SceneType Terminate() override;

private:
    class Game* mGame;

    std::unique_ptr<Actor> skyboxObject;
    std::unique_ptr<Actor> uiObject;
};
