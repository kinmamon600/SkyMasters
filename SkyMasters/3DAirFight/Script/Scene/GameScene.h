#pragma once

#include "SceneBase.h"
#include "../Actor/Actor.h"
#include "../Loader/FighterDataLoader.h"
#include"../Loader/FighterPartsID.h"
#include"../Loader/EnemyLoader.h"
#include "../Component/ModelRenderer.h"
#include "../Game/GameManager.h"

#include<vector>
#include <memory>

/// <summary>
/// メインとなる戦闘シーン
/// </summary>
class GameScene : public SceneBase
{
public:
    GameScene(SceneManager* sceneManager, GameManager* gameManager) : SceneBase(sceneManager, gameManager) {};

    // ロードの準備
    bool PrepareLoadData();

    // 読み込み
    bool Load() override;

    // 初期化
    void Initialize() override;

    // 更新
    void Execute() override;

    // 終了
    SceneType Terminate() override;

private:
    std::unique_ptr<Actor> skyBoxObject;
    std::unique_ptr<Actor> terrainObject;
    std::unique_ptr<Actor> bgmObject;
    std::unique_ptr<Actor> bodyObject;
    std::unique_ptr<Actor> wingObject;
    std::unique_ptr<Actor> diffuserObject;


    FighterDataLoader m_fighterLoader;
    EnemyLoader m_enemyLoader;

    FighterPartsID m_fpID;

    // 画像ハンドル
    int m_reticleImgHandle = -1;    // レティクルの画像ハンドル

    // ３Dモデルハンドル
    int m_bodyModel = -1;
    int m_wingModel = -1;
    int m_diffuserModel = -1;
    int playerModel = -1;
    int planeModel = -1;
    int m_beamModelHandle = -1;     // ビームのモデルハンドル
    std::vector<int> m_enemyModel;

    // スカイボックスハンドル
    int skyHandel = -1;
    int skyTx = -1;

    // 機体のテクスチャマスク
    ModelRenderer::TextureMask m_fighterTexMaskBody = {};   // ボディ部分
    ModelRenderer::TextureMask m_fighterTexMaskCanopy = {}; // キャノピー部分
    ModelRenderer::TextureMask m_fighterTexMaskEmi = {};    // 発光部分

    std::vector<ModelRenderer::TextureMask> m_enemyTexMaskBody;   // 
    std::vector<ModelRenderer::TextureMask> m_enemyTexMaskEmi;    // 発光部分
};
