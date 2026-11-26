// ライブラリ・ヘッダ
#include "GameScene.h"
#include "SceneManager.h"
#include "../Game/Game.h"
#include "../World/WorldSettings.h"

#include<string>

// コンポーネントたち
#include "../Component/SkyboxRenderer.h"
#include "../Component/UIRenderer.h"
#include "../Component/ModelRenderer.h"
#include "../Component/Transform.h"
#include "../Component/Camera.h"
#include "../Component/Input.h"
#include "../Component/PhysicsColliderSphere.h"
#include "../Component/PhysicsColliderBox.h"
#include "../Component/PhysicsColliderCylinder.h"
#include "../Component/Fighter/Fighter.h"
#include "../Component/Fighter/Manual.h"
#include "../Component/FIghter/ManualCamera.h"
#include "../Component/FIghter/Automatic.h"
#include "../Component/FIghter/AutomaticCamera.h"
#include "../Component/Sound.h"
#include "../Game/SoundManager/SoundLilst.h"
#include "../Actor/ActorLayer.h"

#include "../Loader/FighterDataLoader.h"

#include "../Behavior/Enemy/Cannon.h"

bool GameScene::PrepareLoadData()
{
    // CSV読み込み
    if (!m_enemyLoader.StatusLoad()) return false;
    if (!m_enemyLoader.TransformLoad()) return false;

    // 敵の種類数を取得
    int enemyTypeCount = m_enemyLoader.GetTypeCount();

    // 配列サイズ確保
    m_enemyModel.resize(enemyTypeCount);
    m_enemyTexMaskBody.resize(enemyTypeCount);
    m_enemyTexMaskEmi.resize(enemyTypeCount);

    return true;
}

// 読み込み
bool GameScene::Load()
{
    if (!PrepareLoadData()) { return false; }

    // 非同期開始
    SetUseASyncLoadFlag(TRUE);

    m_reticleImgHandle = LoadGraph("../Sprites/Reticle.png");

    std::string bodyModel = "../3DModel/BodyParts" + std::to_string(m_fpID.bodyID) + ".mv1";
    m_bodyModel = MV1LoadModel(bodyModel.c_str()); 
    std::string wingModel = "../3DModel/WingParts" + std::to_string(m_fpID.wingID) + ".mv1";
    m_wingModel = MV1LoadModel(wingModel.c_str());
    std::string diffuserModel = "../3DModel/DiffuserParts" + std::to_string(m_fpID.diffuserID) + ".mv1";
    m_diffuserModel = MV1LoadModel(diffuserModel.c_str());

    //playerModel = MV1LoadModel("../3DModel/testFighter.mv1");
    planeModel = MV1LoadModel("../3DModel/Plane.mv1");
    m_beamModelHandle = MV1LoadModel("../3DModel/Fighter_Bullet.mv1");

    skyHandel = MV1LoadModel("../3DModel/SkyBox/SkyBox.mv1");
    skyTx = LoadGraph("../3DModel/SkyBox/SkyTx.png");

    // 機体のテクスチャマスク設定
    int dif_tx = LoadGraph("../Texture/FighterTextureCo.png");
    int canopy_tx = LoadGraph("../Texture/FighterTextureCanopy.png");
    int emi_tx = LoadGraph("../Texture/FighterTextureEm.png");
    m_fighterTexMaskBody = { dif_tx,
        GetColorF(0.4f, 0.4f, 0.4f, 1.0f),
        GetColorF(0.8f, 0.8f, 0.8f, 1.0f),
        GetColorF(0.1f, 0.1f, 0.1f, 1.0f),
        GetColorF(0.8f, 0.8f, 0.8f, 1.0f),
        64.0f };
    m_fighterTexMaskCanopy = { canopy_tx,
        GetColorF(0.588f, 0.588f, 0.588f, 1.0f),
        GetColorF(1.0f, 1.0f, 1.0f, 1.0f),
        GetColorF(0.1f, 0.1f, 0.1f, 1.0f),
        GetColorF(0.275f, 0.314f, 0.431f, 1.0f),
        100.0f };
    m_fighterTexMaskEmi = { emi_tx,
        GetColorF(0.0f, 0.0f, 0.0f, 1.0f),
        GetColorF(0.0f, 0.0f, 0.0f, 1.0f),
        GetColorF(1.0f, 1.0f, 1.0f, 1.0f),
        GetColorF(0.0f, 0.0f, 0.0f, 1.0f),
        0.0f };

    int enemyTypeCount = m_enemyLoader.GetTypeCount();
    //m_enemyModel.resize(enemyTypeCount);
    for (short i = 0; i < enemyTypeCount; i++)
    {
        std::string difEnemy = "../Texture/Enemy/Enemy_" + std::to_string(i) + "/Enemy_" + std::to_string(i) + "_Diffuse.png";
        int difEnemy_tx = LoadGraph(difEnemy.c_str());
        std::string emiEnemy = "../Texture/Enemy/Enemy_" + std::to_string(i) + "/Enemy_" + std::to_string(i) + "_Emissive.png";
        int emiEnemy_tx = LoadGraph(emiEnemy.c_str());
        m_enemyTexMaskBody[i] = {difEnemy_tx,
           GetColorF(0.4f, 0.4f, 0.4f, 1.0f),
           GetColorF(0.8f, 0.8f, 0.8f, 1.0f),
           GetColorF(0.1f, 0.1f, 0.1f, 1.0f),
           GetColorF(0.8f, 0.8f, 0.8f, 1.0f),
           64.0f };
        m_enemyTexMaskEmi[i] = {emiEnemy_tx,
            GetColorF(0.0f, 0.0f, 0.0f, 1.0f),
            GetColorF(0.0f, 0.0f, 0.0f, 1.0f),
            GetColorF(1.0f, 1.0f, 1.0f, 1.0f),
            GetColorF(0.0f, 0.0f, 0.0f, 1.0f),
            0.0f };
        printfDx("%d, %d\n", difEnemy_tx, emiEnemy_tx);
    }

    // 非同期終了
    SetUseASyncLoadFlag(FALSE);

    m_fpID = p_gameManager->GetFighterPartsID();
    m_fighterLoader.LoadBody();
    m_fighterLoader.LoadWing();
    m_fighterLoader.LoadDiffuser();
    m_fighterLoader.LoadSpecialWeapon();


    //m_enemyLoader.StatusLoad();
    //m_enemyLoader.TransformLoad();
    for (short i = 0; i < enemyTypeCount; i++)
    {
        std::string enemyModelHandle = "../3DModel/Enemy/Enemy_" + std::to_string(i) + "/Enemy_" + std::to_string(i) + ".mv1";

        m_enemyModel[i] = MV1LoadModel(enemyModelHandle.c_str());
    }

    return true;
}

// 初期化
void GameScene::Initialize()
{
    // 芥一の生成
    
    // プレイヤーの生成
    Actor* p_players[4] = {};
    
    for (unsigned short i = 0; i < 4; ++i)
    {
        p_players[i] = new Actor(p_sceneManager->p_game);
        MATRIX mat = MGetIdent();
        mat.m[3][0] = (float)(20 * i);
        mat.m[3][1] = WorldSettings::FloorHeight + 150.0f;
        mat.m[3][2] = 0;
        new Fighter(p_players[i], i + 1, mat, m_beamModelHandle, m_reticleImgHandle);

        ModelRenderer* mr = p_players[i]->GetComponent<ModelRenderer>();
        mr->AddTextureMask(m_fighterTexMaskBody);
        mr->AddTextureMask(m_fighterTexMaskCanopy);
        mr->AddTextureMask(m_fighterTexMaskEmi);
    }

    // スカイドームの生成
    skyBoxObject = std::make_unique<Actor>(p_sceneManager->p_game);
    SkyboxRenderer* skyComp = new SkyboxRenderer(skyBoxObject.get());
    skyComp->SetHandles(skyHandel, skyTx);

    // 地形の生成
    terrainObject = std::make_unique<Actor>(p_sceneManager->p_game);
    terrainObject->SetLayer(ActorLayer::Terrain);

    Transform* terrainTrComp = new Transform(terrainObject.get());
    terrainTrComp->SetPosition(VGet(0.0f, WorldSettings::FloorHeight, 0.0f));

    new PhysicsColliderBox(terrainObject.get(), VGet(0.0f, 0.0f, 0.0f), VGet(WorldSettings::WorldRadius, 1.0f, WorldSettings::WorldRadius), PhysicsCollider::Fixed, 0);

    ModelRenderer* terrainModelComp = new ModelRenderer(terrainObject.get());
    terrainModelComp->SetModelHandle(planeModel);
    
    // 見せかけの地形(背景)の生成
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            if (i == 2 && j == 2)
            {
                continue;
            }

            Actor* act = new Actor(p_sceneManager->p_game);
            Transform* tr = new Transform(act);

            tr->SetPosition(VGet((float)((i - 2) * 8000), WorldSettings::FloorHeight, (float)((j - 2) * 8000)));

            ModelRenderer* renderer = new ModelRenderer(act);
            renderer->SetModelHandle(planeModel);
        }
    }

    // 音源の生成
    bgmObject = std::make_unique<Actor>(p_sceneManager->p_game);
    Sound* bgm = new Sound(bgmObject.get());
    bgm->PlayBGM(BGM::Tutorial_Battle);

    // 敵の生成
    int enemyInstanceCount = m_enemyLoader.GetInstanceCount();
    for (short i = 0; i < enemyInstanceCount; i++)
    {
        Actor* enemy_obj = new Actor(p_sceneManager->p_game);
        enemy_obj->SetLayer(ActorLayer::Enemy);

        Transform* enemyTr = new Transform(enemy_obj);
        VECTOR pos = m_enemyLoader.m_enemyTransform[i].position;
        pos.y += WorldSettings::FloorHeight;
        enemyTr->SetPosition(pos);
        enemyTr->SetRotation(m_enemyLoader.m_enemyTransform[i].rotation);
        //enemyTr->SetScale(m_enemyLoader.m_enemyTransform[i].scale);

        ModelRenderer* enemyModel = new ModelRenderer(enemy_obj);
        enemyModel->SetModelHandle(m_enemyModel[m_enemyLoader.m_enemyTransform[i].enemyID]);
        enemyModel->AddTextureMask(m_enemyTexMaskBody[m_enemyLoader.m_enemyTransform[i].enemyID]);
        enemyModel->AddTextureMask(m_enemyTexMaskEmi[m_enemyLoader.m_enemyTransform[i].enemyID]);

        switch (m_enemyLoader.m_enemyTransform[i].enemyID)
        {
        case 0:
            //new PhysicsColliderCylinder(enemy_obj, VGet(0.0f, 0.0f, 0.0f), 300, 100, PhysicsCollider::Fixed, 1);
            break;

        case 1:
            enemyModel->SetScale(VGet(0.1f, 0.1f, 0.1f));
            new PhysicsColliderSphere(enemy_obj, VGet(0.0f, 0.0f, 0.0f), 30, PhysicsCollider::Fixed, 1);
            new Cannon(enemy_obj, 200, 20, m_beamModelHandle);
            break;

        default:
            break;
        }
    }
}

// 更新
void GameScene::Execute()
{
    //PhysicsColliderSphere* pcbComp = playerObject->GetComponent<PhysicsColliderSphere>();
    //pcbComp->GetDirection(VGet(0, 0, -1));
    //VECTOR vec = SDP::GetDirection(0, VGet(0, 0, -1));
    //printfDx("%f, %f, %f\n", vec.x, vec.y, vec.z);
}

// 終了
SceneType GameScene::Terminate()
{
    // 仮
    return SceneType::TitleScene;
}