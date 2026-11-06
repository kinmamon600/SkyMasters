// ライブラリ・ヘッダ
#include<chrono>
#include<cmath>

#include "SuperDxPhysics.h"

#include "SceneManager.h"

// 各シーンクラスのヘッダ
#include "GameScene.h"

// デストラクタ
SceneManager::~SceneManager()
{
	// シーンを解放
	if (p_currentScene != nullptr)
	{
		//delete currentScene;
		//currentScene = nullptr;
		p_currentScene.reset();
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

// 現在のシーンタイプの取得
SceneStep SceneManager::GetSceneStep() const
{
	return currentStep;
}

// シーンの生成
void SceneManager::CreateScene()
{
	switch (currentSceneType)
	{
	case SceneType::TitleScene:
		break;

	case SceneType::GameScene:
		p_currentScene = std::make_unique<GameScene>(this);
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
	p_currentScene->Initialize();
	currentStep = SceneStep::Execute;

}

// 現在シーンの更新
void SceneManager::Execute()
{
	// 物理演算更新
	SDP::SimulatePhysics();

	// シーン更新
	p_currentScene->Execute();

	// シーン遷移のリクエストがあればシーン終了
	if (p_currentScene->IsSceneChangeRequested())
	{
		currentStep = SceneStep::Terminate;
	}
}

// 現在シーンの終了
void SceneManager::Terminate()
{
	// シーンのリセット
	SceneType nextSceneType = p_currentScene->Terminate();
	//delete currentScene;
	//currentScene = nullptr;
	p_currentScene.reset();

	// 物理世界のリセット
	SDP::ResetPhysicsWorld();

	// 次のシーンを設定
	currentSceneType = nextSceneType;
	currentStep = SceneStep::Load;
}

// 現在シーンの読み込み
void SceneManager::Load()
{
	if (p_currentScene == nullptr) 
	{
		CreateScene();

		if (p_currentScene == nullptr)
		{
			return;
		}
	}

	// 非同期処理開始
	if (!isLoadStarted)
	{
		SceneBase* scene = p_currentScene.get();

		loadTask = std::async(std::launch::async, [scene]()
		{
			return scene->Load();
		});

		isLoadStarted = true;
	}

	// 非同期処理完了の確認
	if (loadTask.valid() && loadTask.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
	{
		// 非同期処理の終了を受け取る
		bool loadSucceeded = loadTask.get();
		isLoadStarted = false;

		if (loadSucceeded)
		{
			// 読み込み成功時のみ初期化
			currentStep = SceneStep::Initialize;
		}
		else
		{
			p_currentScene.reset();
			currentSceneType = SceneType::Exit;
		}
	}
	else
	{
		DrawLoading();
	}
}

// Loadingクルクルの表示
void SceneManager::DrawLoading()
{
	const int centerX = 640;
	const int centerY = 360;
	const int radius = 30;
	const int dotCount = 8;

	for (int i = 0; i < dotCount; i++)
	{
		// １個ずつ円周上の配置
		double angle = (loadingAngle + i * 360 / dotCount) * DX_PI / 180.0;

		int x = centerX + static_cast<int>(std::cos(angle) * radius);
		int y = centerY + static_cast<int>(std::sin(angle) * radius);

		// 後ろの円ほど薄い色
		int brightness = 80 + i * 22;
		if (brightness > 255)
		{
			brightness = 255;
		}

		// 次のフレームで回転させる
		DrawCircle(x, y, 5, GetColor(brightness, brightness, brightness), TRUE);
	}

	loadingAngle = (loadingAngle + 6) % 360;
}