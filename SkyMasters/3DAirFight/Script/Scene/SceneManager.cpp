// ライブラリ・ヘッダ
#include "SceneManager.h"

// 各シーンクラスのヘッダ


// デストラクタ
SceneManager::~SceneManager()
{
	// シーンを解放
	if (currentScene != nullptr)
	{
		//delete currentScene;
		//currentScene = nullptr;
		currentScene.reset();
	}
}

// シーンの更新
void SceneManager::Update()
{
	switch (currentStep)
	{
	case SceneStep::Initialize:
		Initialize();
		break;

	case SceneStep::Update:
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
void SceneManager::CreateScene()
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
void SceneManager::Initialize()
{
	// シーンを生成・初期化
	CreateScene();
	currentScene->Initialize();
	currentStep = SceneStep::Update;

}

// 現在シーンの更新
void SceneManager::Execute()
{
	currentScene->Execute();

	// シーン遷移のリクエストがあればシーン終了
	if (currentScene->IsSceneChangeRequested())
	{
		currentStep = SceneStep::Terminate;
	}
}

// 現在シーンの終了
void SceneManager::Terminate()
{
	// 現在シーンの終了
	SDP::ResetPhysicsWorld();
	SceneType nextSceneType = currentScene->Terminate();
	//delete currentScene;
	//currentScene = nullptr;
	currentScene.reset();

	// 次のシーンを設定
	currentSceneType = nextSceneType;
	currentStep = SceneStep::Initialize;
}

// 現在シーンの読み込み
void SceneManager::Load()
{
	// シーンがまだなければ生成
	if (currentScene == nullptr)
	{
		CreateScene();
	}

	// 読み込みが完了したら初期化へ進む
	if (currentScene->Load())
	{
		currentStep = SceneStep::Initialize;
	}
}
