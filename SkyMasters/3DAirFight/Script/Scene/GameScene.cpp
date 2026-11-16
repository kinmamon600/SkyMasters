#include "GameScene.h"
#include "SceneManager.h"
#include "../Game/Game.h"

// コンポーネントたち
#include "../Component/SkyboxRenderer.h"
#include "../Component/UIRenderer.h"
#include "../Component/ModelRenderer.h"
#include "../Component/Transform.h"
#include "../Component/Camera.h"
#include "../Component/Input.h"
#include "../Component/PhysicsColliderSphere.h"
#include "../Component/PhysicsColliderBox.h"
#include "../Component/Fighter/Fighter.h"
#include "../Component/Fighter/Manual.h"
#include "../Component/FIghter/ManualCamera.h"
#include "../Component/FIghter/Automatic.h"
#include "../Component/FIghter/AutomaticCamera.h"

#include "../Component/Fighter/FighterDataLoader.h"

#include "SuperDxPhysics.h"

// 読み込み
bool GameScene::Load()
{
    m_loader.LoadBody();
    m_loader.LoadWing();
    m_loader.LoadDiffuser();
    m_loader.LoadSpecialWeapon();

    playerModel = MV1LoadModel("../3DModel/testFighter.mv1");

    skyHandel = MV1LoadModel("../3DModel/SkyBox/SkyBox.mv1");
    skyTx = LoadGraph("../3DModel/SkyBox/SkyTx.png");

    return true;
}

// 初期化
void GameScene::Initialize()
{
    // 芥一の生成
    playerObject = std::make_unique<Actor>(p_sceneManager->p_game);
    skyBoxObject = std::make_unique<Actor>(p_sceneManager->p_game);
    cameraObject = std::make_unique<Actor>(p_sceneManager->p_game);

    // コンポーネントを生成
    new Transform(playerObject.get());
    new PhysicsColliderSphere(playerObject.get(),VGet(0.0f, 0.0f, 0.0f),30,PhysicsCollider::Active,1);
    //new PhysicsColliderBox(playerObject.get(), VGet(0.0f, 0.0f, 0.0f), VGet(1.0f, 1.0f, 1.0f), PhysicsCollider::Active, 1);
    new Input(playerObject.get());
    new ModelRenderer(playerObject.get());
    new Fighter(playerObject.get(), cameraObject.get());
    new Manual(playerObject.get());
    new Automatic(playerObject.get());

    new Camera(cameraObject.get());
    new ManualCamera(cameraObject.get());
    new AutomaticCamera(cameraObject.get());

    new SkyboxRenderer(skyBoxObject.get());

    ModelRenderer* modelComp = playerObject->GetComponent<ModelRenderer>();
    modelComp->SetModelHandle(playerModel);
    modelComp->SetScale(VGet(0.1f, 0.1f, 0.1f));

    Camera* cameraComp = cameraObject->GetComponent<Camera>();
    cameraComp->SetDispArea(0, 0, 1920 / 2, 1080 / 2);
    cameraComp->SetDispCenter(1920 / 4, 1080 / 4);
    cameraComp->SetPosition(VGet(0,100,400));

    SkyboxRenderer* skyComp = skyBoxObject->GetComponent<SkyboxRenderer>();
    skyComp->SetHandles(skyHandel, skyTx);
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
    skyBoxObject.reset();
    //uiObject.reset();
    //modelObject.reset();
    playerObject.reset();
    cameraObject.reset();

    // 仮
    return SceneType::Exit;
}