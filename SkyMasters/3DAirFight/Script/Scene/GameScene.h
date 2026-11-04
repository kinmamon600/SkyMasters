#pragma once

#include "SceneBase.h"
#include "../Actor/Actor.h"
#include "../Game/Game.h"
#include "../Component/FIghter/FighterDataLoader.h"

#include <memory>

class GameScene : public SceneBase
{
public:
    GameScene(SceneManager* sceneManager) : SceneBase(sceneManager) {};

    // 読み込み
    bool Load() override;

    // 初期化
    void Initialize() override;

    // 更新
    void Execute() override;

    // 終了
    SceneType Terminate() override;

private:
    // 
    std::unique_ptr<Actor> skyboxObject;
    std::unique_ptr<Actor> uiObject;
    std::unique_ptr<Actor> modelObject;

    FighterDataLoader m_loader;

    // 画像ハンドル
    int testHandle = -1;

    // ３Dモデルハンドル
    int modelHandle = -1;
};
