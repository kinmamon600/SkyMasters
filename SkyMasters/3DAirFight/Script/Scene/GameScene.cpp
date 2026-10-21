#include"GameScene.h"
#include"SceneManager.h"
#include"../Component/SkyboxRenderer.h"
#include"../Component/UIRenderer.h"
#include"../Game/Game.h"
<<<<<<< HEAD
=======

GameScene::GameScene(Game* game) 
    :mGame(game)
{

}
>>>>>>> bcc4a45b3cb946afa142413c4c781f3eb88fe6cd

bool GameScene::Load()
{
    // モデル読み込み
    return true;
}

void GameScene::Initialize()
{
<<<<<<< HEAD
    skyboxObject = std::make_unique<Actor>(p_sceneManager->p_game);
    uiObject = std::make_unique<Actor>(p_sceneManager->p_game);

    // コンポーネントを生成
    auto* skyboxRenderer = new SkyboxRenderer(skyboxObject.get());
    auto* uiRenderer = new UIRenderer(uiObject.get());

	skyboxObject->AddComponent(skyboxRenderer);
	uiObject->AddComponent(uiRenderer);
=======
	skyboxObject = std::make_unique<Actor>(mGame);
	uiObject = std::make_unique<Actor>(mGame);

	skyboxObject->AddComponent(new SkyboxRenderer(skyboxObject.get()));

	uiObject->AddComponent(new UIRenderer(uiObject.get()));
>>>>>>> bcc4a45b3cb946afa142413c4c781f3eb88fe6cd
}

void GameScene::Execute()
{
    // 1. skybox

    // 2. 通常の3Dオブジェクト


    // 3. 2D UI
}

SceneType GameScene::Terminate()
{
    skyboxObject.reset();
    uiObject.reset();

    // 仮
    return SceneType::Exit;
}