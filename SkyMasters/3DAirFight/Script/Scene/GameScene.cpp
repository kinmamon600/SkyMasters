#include "GameScene.h"
#include "SceneManager.h"
#include "../Component/SkyboxRenderer.h"
#include "../Component/UIRenderer.h"
#include "../Component/ModelRenderer.h"
#include "../Component/Transform.h"
#include "../Game/Game.h"


#include "../Component/FIghter/FighterDataLoader.h"

// 読み込み
bool GameScene::Load()
{
    m_loader.LoadBody();
    m_loader.LoadWing();
    m_loader.LoadDiffuser();
    m_loader.LoadSpecialWeapon();

    testHandle = LoadGraph ("../Sprites/bomb.png");

    modelHandle = MV1LoadModel("../3DModle/Alice.mv1");
    return true;
}

// 初期化
void GameScene::Initialize()
{
    skyboxObject = std::make_unique<Actor>(p_sceneManager->p_game);
    uiObject = std::make_unique<Actor>(p_sceneManager->p_game);
    modelObject = std::make_unique<Actor>(p_sceneManager->p_game);

    // コンポーネントを生成
    new SkyboxRenderer(skyboxObject.get());
    new UIRenderer(uiObject.get());
    new ModelRenderer(modelObject.get());
    new Transform(uiObject.get());
    new Transform(modelObject.get());

    UIRenderer* uiComp = uiObject->GetComponent<UIRenderer>();
    uiComp->SetGrphHandle(testHandle);
    ModelRenderer* modelComp = modelObject->GetComponent<ModelRenderer>();
    modelComp->SetModelHandle(modelHandle);
}

// 更新
void GameScene::Execute()
{
    Transform* uiTr = uiObject->GetComponent<Transform>();

    VECTOR tr = uiTr->GetPosition();
    uiTr->SetPosition(VGet(tr.x + 1.0f, tr.y + 1.0f, 0.0f));

    float Z = uiTr->GetRotation().z;
    uiTr->SetRotation(VGet(0.0f, 0.0f, Z + 1.0f));

    Transform* modTr = modelObject->GetComponent<Transform>();

    VECTOR t = modTr->GetPosition();
    modTr->SetPosition(VGet(t.x + 1.0f, t.y + 1.0f, 0.0f));

    float Y = modTr->GetRotation().y;
    modTr->SetRotation(VGet(0.0f, Y + 1.0f, 0.0f));
}

// 終了
SceneType GameScene::Terminate()
{
    skyboxObject.reset();
    uiObject.reset();

    // 仮
    return SceneType::Exit;
}