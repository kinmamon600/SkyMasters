#include"GameScene.h"
#include"SceneManager.h"
#include"../Component/SkyboxRenderer.h"
#include"../Component/UIRenderer.h"
#include"../Component/ModelRenderer.h"
#include"../Component/Transform.h"
#include"../Game/Game.h"

bool GameScene::Load()
{
    testHandle = LoadGraph("../Sprites/bomb.png");
    modelHnadle = MV1LoadModel()
    return true;
}

void GameScene::Initialize()
{
    skyboxObject = std::make_unique<Actor>(p_sceneManager->p_game);
    uiObject = std::make_unique<Actor>(p_sceneManager->p_game);
    modelObject=std::make_unique<Actor>(p_sceneManager->p_game);

    // コンポーネントを生成
    new SkyboxRenderer(skyboxObject.get());
    new UIRenderer(uiObject.get());
    new ModelRenderer(uiObject.get());
    new Transform(uiObject.get());

    auto* uiComp = uiObject->GetComponent<UIRenderer>();
    uiComp->SetGrphHandle(testHandle);
    auto* modelComp = modelObject->GetComponent<ModelRenderer>();
    modelComp->SetModelHandle()
}

void GameScene::Execute()
{
    Transform* uiTr = uiObject->GetComponent<Transform>();

    VECTOR tr = uiTr->GetPosition();
    uiTr->SetPosition(VGet(tr.x + 1.0f, tr.y + 1.0f, 0.0f));

    float Z = uiTr->GetRotation().z;
    uiTr->SetRotation(VGet(0.0f, 0.0f, Z + 1.0f));
}

SceneType GameScene::Terminate()
{
    skyboxObject.reset();
    uiObject.reset();

    // 仮
    return SceneType::Exit;
}