// ライブラリ・ヘッダ
#include "MainScene.h"

// 各シーンクラスのヘッダ


// デストラクタ
MainScene::~MainScene()
{
	// シーンを解放
	if (currentScene != nullptr)
	{
		delete currentScene;
		currentScene = nullptr;
	}
}

// シーンの更新
void MainScene::Update()
{
	switch (currentStep)
	{
	case SceneStep::Initialize:
		Initialize();
		break;

	case SceneStep::Execute:
		Execute();
		break;

	case SceneStep::Terminate:
		Terminate();
		break;

	case SceneStep::Load:
		Load();
		break;
	}
}

// シーンの生成
void MainScene::CreateScene()
{
	switch (currentSceneType)
	{
	case SceneType::TitleScene:
		break;

	case SceneType::GameScene:
		break;

	case SceneType::Exit:
		break;

	default:
		break;
	}
}

// 現在シーンの初期化
void MainScene::Initialize()
{
	// シーンを生成・初期化
	CreateScene();
	currentScene->Initialize();
	currentStep = SceneStep::Execute;
}

// 現在シーンの更新
void MainScene::Execute()
{
	currentScene->Execute();

	// シーン遷移のリクエストがあればシーン終了
	if (currentScene->IsSceneChangeRequested())
	{
		currentStep = SceneStep::Terminate;
	}
}

// 現在シーンの終了
void MainScene::Terminate()
{
	// 現在シーンの終了
	SDP::ResetPhysicsWorld();
	SceneType nextSceneType = currentScene->Terminate();
	delete currentScene;
	currentScene = nullptr;

	// 次のシーンを設定
	currentSceneType = nextSceneType;
	currentStep = SceneStep::Initialize;
}

// 現在シーンの読み込み
void MainScene::Load()
{

}
