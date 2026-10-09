// ライブラリ・ヘッダ
#include "SceneManager.h"

#include<chrono>
#include<cmath>

// 各シーンクラスのヘッダ


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
	p_currentScene->Initialize();
	currentStep = SceneStep::Update;

}

// 現在シーンの更新
void SceneManager::Execute()
{
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
	// 現在シーンの終了
	SDP::ResetPhysicsWorld();
	SceneType nextSceneType = p_currentScene->Terminate();
	//delete currentScene;
	//currentScene = nullptr;
	p_currentScene.reset();

	// 次のシーンを設定
	currentSceneType = nextSceneType;
	currentStep = SceneStep::Initialize;
}

// 現在シーンの読み込み
void SceneManager::Load()
{
	// 非同期処理をまだ開始していない場合
	if (!isLoadStarted)
	{
		SceneBase* scene = p_currentScene.get();

		loadTask = std::async(std::launch::async, [scene]()
		{
			scene->Load();
		});

		isLoadStarted = true;
	}

	// 非同期処理が終わったか確認
	if (loadTask.valid() && loadTask.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
	{
		// 非同期処理の終了を受け取る
		loadTask.get();

		isLoadStarted = false;
		currentStep = SceneStep::Initialize;
	}
	else
	{
		DrawLoading();
	}
}

// ローディングクルクルの表示
void SceneManager::DrawLoading()
{
	const int centerX = 640;
	const int centerY = 360;
	const int radius = 30;
	const int dotCount = 8;

	for (int i = 0; i < dotCount; i++)
	{
		// １個ずつ円周上の配置
		double angle = (loadingAngle + i * 360 / dotCount) * 3.14159265 / 180.0;

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