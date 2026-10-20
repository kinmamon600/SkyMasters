#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H

// ライブラリ・ヘッダ
#include "SuperDxPhysics.h"
#include "SceneDefine.h"
#include "SceneBase.h"

#include <memory>
#include <future>

class Game;

/// <summary>
/// シーンを管理する
/// </summary>
class SceneManager {
public:
	// コンストラクタ
	SceneManager(Game* game) : p_game(game), p_currentScene(nullptr), currentSceneType(SceneType::TitleScene), currentStep(SceneStep::Load) {}

	// デストラクタ
	~SceneManager();
	
	// シーンの更新
	void Update();

	void DrawLoading();

	// ゲーム
	Game* p_game;
private:

	// 現在のシーン
	std::unique_ptr<SceneBase> p_currentScene;

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

	// 非同期処理の管理
	std::future<bool>loadTask;		// 非同期処理完了を確認
	bool isLoadStarted = false;		// 非同期処理を開始したか記録

	// ロードアニメーションの管理
	int loadingAngle = 0;
};

#endif