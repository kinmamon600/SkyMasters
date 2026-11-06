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
#include "../Component/PhysicsColliderBox.h"
#include "../Component/Fighter/Fighter.h"

#include "../Component/Fighter/FighterDataLoader.h"

// 読み込み
bool GameScene::Load()
{
    m_loader.LoadBody();
    m_loader.LoadWing();
    m_loader.LoadDiffuser();
    m_loader.LoadSpecialWeapon();

    playerModel = MV1LoadModel("../3DModel/testFighter.mv1");

    return true;
}

// 初期化
void GameScene::Initialize()
{
    // インスタンスの生成
    playerObject = std::make_unique<Actor>(p_sceneManager->p_game);

    // コンポーネントを生成
    new Transform(playerObject.get());
    new Fighter(playerObject.get());
    new PhysicsColliderBox(playerObject.get(),VGet(0,0,0),VGet(1,1,1),PhysicsCollider::Active,100);
    new Input(playerObject.get());
    new ModelRenderer(playerObject.get());

    ModelRenderer* modelComp = playerObject->GetComponent<ModelRenderer>();
    modelComp->SetModelHandle(playerModel);

}

// 更新
void GameScene::Execute()
{

}

// 終了
SceneType GameScene::Terminate()
{
    //skyboxObject.reset();
    //uiObject.reset();
    //modelObject.reset();
    playerObject.reset();

    // 仮
    return SceneType::Exit;
}