#pragma once

#include "SceneBase.h"
#include "../Actor/Actor.h"
#include "../Game/Game.h"
#include "../Component/FIghter/FighterDataLoader.h"

#include <memory>

/// <summary>
/// メインとなる戦闘シーン
/// </summary>
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
    // ゲームオブジェクト
    std::unique_ptr<Actor> playerObject;
    std::unique_ptr<Actor> modelObject;
    //std::unique_ptr<Actor> skyboxObject;
    //std::unique_ptr<Actor> uiObject;

    FighterDataLoader m_loader;

    // 画像ハンドル

    // ３Dモデルハンドル
    int playerModel = -1;
};
