#include"GameScene.h"
#include"../Component/SkyboxRenderer.h"
#include"../Component/UIRenderer.h"
#include"../Game/Game.h"

GameScene::GameScene(Game* game) 
    :mGame(game)
{

}

bool GameScene::Load()
{
    // モデル読み込み
    return true;
}

void GameScene::Initialize()
{
	skyboxObject = std::make_unique<Actor>(mGame);
	uiObject = std::make_unique<Actor>(mGame);

	skyboxObject->AddComponent(new SkyboxRenderer(skyboxObject.get()));

	uiObject->AddComponent(new UIRenderer(uiObject.get()));
}

void GameScene::Execute()
{
    // 1. skybox
    skyboxObject->Draw();

    // 2. 通常の3Dオブジェクト
    for (auto& actor : mActors)
    {
        actor->Draw();
    }

    // 3. 2D UI
    uiObject->Draw();
}

SceneType GameScene::Terminate()
{
    skyboxObject.reset();
    uiObject.reset();

    // 仮
    return SceneType::Exit;
}