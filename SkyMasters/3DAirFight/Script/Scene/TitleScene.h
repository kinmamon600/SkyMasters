#pragma once

#include "SceneBase.h"
#include "../Actor/Actor.h"
#include "../Game/Game.h"
#include "../Component/FIghter/FighterDataLoader.h"
#include "../Component/ButtonManager.h"

class TitleScene :public SceneBase
{
public:
    TitleScene(SceneManager* sceneManager) : SceneBase(sceneManager) {};

    // “Ç‚İ‚İ
    bool Load() override;

    // ‰Šú‰»
    void Initialize() override;

    // XV
    void Execute() override;

    // I—¹
    SceneType Terminate() override;

private:
    std::unique_ptr<Actor> startButtonObject;
    std::unique_ptr<Actor> endButtonObject;
    std::unique_ptr<Actor> buttonManagerObject;
    std::unique_ptr<Actor> cameraObject;

    int startHandle = -1;
    int endHandle = -1;
};