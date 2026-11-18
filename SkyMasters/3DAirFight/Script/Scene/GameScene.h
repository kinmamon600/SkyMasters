#pragma once

#include "SceneBase.h"
#include "../Actor/Actor.h"
#include "../Loader/FighterDataLoader.h"

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
    std::unique_ptr<Actor> skyBoxObject;
    //std::unique_ptr<Actor> uiObject;
    //std::unique_ptr<Actor> modelObject;
    std::unique_ptr<Actor> cameraObject;

    FighterDataLoader m_loader;

    // 画像ハンドル

    // ３Dモデルハンドル
    int playerModel = -1;

    // スカイボックスハンドル
    int skyHandel = -1;
    int skyTx = -1;
};
