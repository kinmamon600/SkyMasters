#ifndef _MAINSCENE_H
#define _MAINSCENE_H

// ライブラリ・ヘッダ
#include "SuperDxPhysics.h"
#include "SceneDefine.h"
#include "SceneBase.h"
#include "GameInput.h"
#include "Player.h"

/// <summary>
/// シーンを管理する
/// </summary>
class MainScene {
public:
	// コンストラクタ
	MainScene(PlayerSettings* pl1_set, PlayerSettings* pl2_set, GameInput* pl1_input, GameInput* pl2_input) 
		: player1Settings(pl1_set), player2Settings(pl2_set), player1Input(pl1_input), player2Input(pl2_input),
		currentScene(nullptr) , currentSceneType(SceneType::TitleMenuScene) , currentStep(SceneStep::Initialize) {}

	// デストラクタ
	~MainScene();
	
	// シーンの更新
	void Update();

private:
	// 現在のシーン
	SceneBase* currentScene;

	// 現在のシーンタイプ
	SceneType currentSceneType;

	// 現在の処理段階
	SceneStep currentStep;

	// 各プレイヤーの設定
	PlayerSettings* player1Settings;
	PlayerSettings* player2Settings;

	// 各プレイヤーの入力
	GameInput* player1Input;
	GameInput* player2Input;

	// シーンの生成
	void CreateScene();

	// 現在シーンの初期化
	void Initialize();

	// 現在シーンの実行
	void Execute();

	// 現在シーンの終了
	void Terminate();
};

#endif