#ifndef _MAINSCENE_H
#define _MAINSCENE_H

// ライブラリ・ヘッダ
#include "SuperDxPhysics.h"
#include "SceneDefine.h"
#include "SceneBase.h"

#include <memory>

/// <summary>
/// シーンを管理する
/// </summary>
class SceneManager {
public:
	// コンストラクタ
	SceneManager() : currentScene(nullptr) , currentSceneType(SceneType::TitleScene) , currentStep(SceneStep::Initialize) {}

	// デストラクタ
	~SceneManager();
	
	// シーンの更新
	void Update();

private:
	// 現在のシーン
	std::unique_ptr<SceneBase> currentScene;

	// 現在のシーンタイプ
	SceneType currentSceneType;

	// 現在の処理段階
	SceneStep currentStep;

	// シーンの生成
	void CreateScene();

	// 現在シーンの初期化
	void Initialize();

	// 現在シーンの実行
	void Execute();

	// 現在シーンの終了
	void Terminate();

	// 現在シーンの読み込み
	void Load();

	bool isLoadStarted = false;
};

#endif