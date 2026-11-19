#pragma once

#include "SceneBase.h"
#include "../Actor/Actor.h"
#include "../Loader/FighterDataLoader.h"
#include "../Component/ModelRenderer.h"

#include <memory>

/// <summary>
/// メインとなる戦闘シーン
/// </summary>
class GameScene : public SceneBase
{
public:
    GameScene(SceneManager* sceneManager, GameManager* gameManager) : SceneBase(sceneManager, gameManager) {};

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
    std::unique_ptr<Actor> terrainObject;

    FighterDataLoader m_loader;

    // 画像ハンドル

    // ３Dモデルハンドル
    int playerModel = -1;
    int planeModel = -1;
    int m_beamModelHandle = -1;

    // スカイボックスハンドル
    int skyHandel = -1;
    int skyTx = -1;

    // 機体のテクスチャマスク
    ModelRenderer::TextureMask m_fighterTexMaskBody = {};   // ボディ部分
    ModelRenderer::TextureMask m_fighterTexMaskCanopy = {}; // キャノピー部分
    ModelRenderer::TextureMask m_fighterTexMaskEmi = {};    // 発光部分
};
