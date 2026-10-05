// ライブラリ・ヘッダ
#include "MainScene.h"

// 各シーンクラスのヘッダ
#include "TitleMenuScene.h"
#include "SelectMenuScene.h"
#include "GameScene.h"

MainScene::~MainScene()
{
	// シーンを解放
	if (currentScene != nullptr)
	{
		delete currentScene;
		currentScene = nullptr;
	}
}

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
	}
}

void MainScene::CreateScene()
{
	switch (currentSceneType)
	{
	case SceneType::TitleMenuScene:
		currentScene = new TitleMenuScene(player1Input);
		//printfDx("タイトルメニュー生成\n");
		break;

	case SceneType::SelectMenuScene:
		currentScene = new SelectMenuScene(player1Settings, player2Settings, player1Input, player2Input);
		//printfDx("セレクトメニュー生成\n");
		break;

	case SceneType::GameScene:
		currentScene = new GameScene(player1Settings, player2Settings, player1Input, player2Input);
		//printfDx("ゲームシーン生成\n");
		break;

	case SceneType::CreditScene:
		//printfDx("クレジットシーン生成\n");
		break;

	case SceneType::Exit:
		//printfDx("ゲームの終了\n");
		break;

	default:
		break;
	}
}

void MainScene::Initialize()
{
	// 描画範囲・注視点を全画面に初期化
	SetDrawArea(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y);
	SetCameraScreenCenter(WINDOW_CENTER_X, WINDOW_CENTER_Y);

	// シーンを生成・初期化
	CreateScene();
	currentScene->Initialize();
	currentStep = SceneStep::Execute;
}

void MainScene::Execute()
{
	currentScene->Execute();

	if (currentScene->IsSceneChangeRequested())
	{
		currentStep = SceneStep::Terminate;
	}
}

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

	//printfDx("シーン遷移\n");
}
