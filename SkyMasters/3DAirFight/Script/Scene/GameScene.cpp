#include "GameScene.h"
#include "SceneManager.h"
#include "../Game/Game.h"

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
#include "../Actor/ActorLayer.h"

#include "../Loader/FighterDataLoader.h"

#include "SuperDxPhysics.h"

// 読み込み
bool GameScene::Load()
{
    // 非同期開始
    SetUseASyncLoadFlag(TRUE);

    std::string bodyModel = "../3DModel/BodyParts" + std::to_string(m_fpID.bodyID) + ".mv1";
    m_bodyModel = MV1LoadModel(bodyModel.c_str()); 
    std::string wingModel = "../3DModel/WingParts" + std::to_string(m_fpID.wingID) + ".mv1";
    m_wingModel = MV1LoadModel(wingModel.c_str());
    std::string diffuserModel = "../3DModel/DiffuserParts" + std::to_string(m_fpID.diffuserID) + ".mv1";
    m_diffuserModel = MV1LoadModel(diffuserModel.c_str());

    playerModel = MV1LoadModel("../3DModel/testFighter.mv1");
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
    m_enemyModel.resize(enemyTypeCount);
    for (short i = 0; i < enemyTypeCount; i++)
    {
        std::string difEnemy = "../Texture/Enemy/Enemy_0/Enemy_" + std::to_string(i) + "_Diffuse.png";
        int difEnemy_tx = LoadGraph(difEnemy.c_str());
        std::string emiEnemy = "../Texture/Enemy/Enemy_0/Enemy_" + std::to_string(i) + "_Emissive.png";
        int emiEnemy_tx = LoadGraph(emiEnemy.c_str());
        m_enemyTexMaskBody[i] = {difEnemy_tx,
           GetColorF(0.4f, 0.4f, 0.4f, 1.0f),
           GetColorF(0.8f, 0.8f, 0.8f, 1.0f),
           GetColorF(0.1f, 0.1f, 0.1f, 1.0f),
           GetColorF(0.8f, 0.8f, 0.8f, 1.0f),
           64.0f };
        m_enemyTexMaskEmi = { emiEnemy_tx,
            GetColorF(0.0f, 0.0f, 0.0f, 1.0f),
            GetColorF(0.0f, 0.0f, 0.0f, 1.0f),
            GetColorF(1.0f, 1.0f, 1.0f, 1.0f),
            GetColorF(0.0f, 0.0f, 0.0f, 1.0f),
            0.0f };
    }

    // 非同期終了
    SetUseASyncLoadFlag(FALSE);

    m_fpID = p_gameManager->GetFighterPartsID();
    m_fighterLoader.LoadBody();
    m_fighterLoader.LoadWing();
    m_fighterLoader.LoadDiffuser();
    m_fighterLoader.LoadSpecialWeapon();


    m_enemyLoader.StatusLoad();
    m_enemyLoader.TransformLoad();
    m_enemyModel.resize(enemyTypeCount);
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
    playerObject = std::make_unique<Actor>(p_sceneManager->p_game);
    playerObject->SetLayer(ActorLayer::Player);
    skyBoxObject = std::make_unique<Actor>(p_sceneManager->p_game);
    cameraObject = std::make_unique<Actor>(p_sceneManager->p_game);
    terrainObject = std::make_unique<Actor>(p_sceneManager->p_game);
    bodyObject = std::make_unique<Actor>(p_sceneManager->p_game);
    wingObject = std::make_unique<Actor>(p_sceneManager->p_game);
    diffuserObject = std::make_unique<Actor>(p_sceneManager->p_game);

    int enemyInstanceCount = m_enemyLoader.GetInstanceCount();
    enemyObject.resize(enemyInstanceCount);
    for (short i = 0; i < enemyInstanceCount; i++)
    {
        enemyObject[i] = std::make_unique<Actor>(p_sceneManager->p_game);
        Transform* enemyTr = new Transform(enemyObject[i].get());
        enemyTr->SetPosition(m_enemyLoader.m_enemyTransform[i].position);
        enemyTr->SetRotation(m_enemyLoader.m_enemyTransform[i].rotation);
        enemyTr->SetScale(m_enemyLoader.m_enemyTransform[i].scale);
    }

    // Transform
    new Transform(playerObject.get());
    new Transform(bodyObject.get());
    new Transform(wingObject.get());
    new Transform(diffuserObject.get());
    new Transform(terrainObject.get());
    
    // 物理
    new PhysicsColliderBox(terrainObject.get(), VGet(0.0f, 0.0f, 0.0f), VGet(30.0f, 30.0f, 30.0f), PhysicsCollider::Trigger, 0);
    new PhysicsColliderSphere(playerObject.get(), VGet(0.0f, 0.0f, 0.0f), 30, PhysicsCollider::Active, 1);
    //for (short i = 0; i < enemyInstanceCount; i++)
    //{
    //    new PhysicsColliderCylinder(enemyObject[i].get(), VGet(0.0f, 0.0f, 0.0f), 30,10, PhysicsCollider::Fixed, 1);
    //    ModelRenderer* enemyModel = new ModelRenderer(enemyObject[i].get());
    //    enemyModel->SetModelHandle(m_enemyModel[m_enemyLoader.m_enemyTransform[i].enemyID]);
    //    enemyModel->SetScale(VGet(0.1f,0.1f,0.1f));
    //    enemyModel->AddTextureMask(m_enemyTexMaskBody[m_enemyLoader.m_enemyTransform[i].enemyID]);
    //    enemyModel->AddTextureMask(m_enemyTexMaskEmi);
    //}
    
    // カメラ
    new ManualCamera(cameraObject.get());
    new AutomaticCamera(cameraObject.get());
    Camera* cameraComp = new Camera(cameraObject.get());
    cameraComp->SetDispArea(0, 0, 1920 / 2, 1080 / 2);
    cameraComp->SetDispCenter(1920 / 4, 1080 / 4);
    cameraComp->SetPosition(VGet(0, 100, 400));

    ModelRenderer* bodyModel = new ModelRenderer(bodyObject.get());
    bodyModel->SetModelHandle(m_bodyModel);
    bodyModel->SetScale(VGet(0.1f, 0.1f, 0.1f));
    ModelRenderer* wingModel = new ModelRenderer(wingObject.get());
    wingModel->SetModelHandle(m_wingModel);
    wingModel->SetScale(VGet(0.1f, 0.1f, 0.1f));
    ModelRenderer* diffuserModel = new ModelRenderer(diffuserObject.get());
    diffuserModel->SetModelHandle(m_diffuserModel);
    diffuserModel->SetScale(VGet(0.1f, 0.1f, 0.1f));
    
    // プレイヤー
    //new PhysicsColliderBox(playerObject.get(), VGet(0.0f, 0.0f, 0.0f), VGet(1.0f, 1.0f, 1.0f), PhysicsCollider::Active, 1);
    new Input(playerObject.get());
    new ModelRenderer(playerObject.get());
    new Fighter(playerObject.get(), cameraObject.get(), m_beamModelHandle);
    new Manual(playerObject.get());
    new Automatic(playerObject.get());
    ModelRenderer* modelComp = new ModelRenderer(playerObject.get());
    modelComp->SetModelHandle(playerModel);
    modelComp->SetScale(VGet(0.1f, 0.1f, 0.1f));
    
    // 機体のテクスチャー
    modelComp->AddTextureMask(m_fighterTexMaskBody);
    modelComp->AddTextureMask(m_fighterTexMaskCanopy);
    modelComp->AddTextureMask(m_fighterTexMaskEmi);
    
    // スカイボックス
    SkyboxRenderer* skyComp = new SkyboxRenderer(skyBoxObject.get());
    skyComp->SetHandles(skyHandel, skyTx);
    
    // 地形
    //new PhysicsColliderSphere(terrainObject.get(), VGet(0.0f, 0.0f, 0.0f), 300, PhysicsCollider::Trigger, 0);
    ModelRenderer* terrainModelComp = new ModelRenderer(terrainObject.get());
    terrainModelComp->SetModelHandle(planeModel);
    terrainModelComp->SetScale(VGet(0.1f, 1.0f, 0.1f));
    Transform* terrainTrComp = terrainObject->GetComponent<Transform>();
    terrainTrComp->SetPosition(VGet(0.0f, -1000.0f, 0.0f));
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
    return SceneType::Exit;
}