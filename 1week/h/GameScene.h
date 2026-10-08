#ifndef _GAMESCENE_H
#define _GAMESCENE_H

// ライブラリ・ヘッダ
#include "DxLib.h"

#include "FontHandle.h"

#include "SceneBase.h"
#include "GameInput.h"
#include "Player.h"
#include "Terrain.h"
#include "Sky.h"

// 定数
// ゲームシーンのカメラ設定値
const float GAMESCENE_CAMNEAR = 15.0f;
const float GAMESCENE_CAMFAR = 5000.0f;

// 導入・終了演出の時間
const double GAMESCENE_INTRO_TIME = 3.0;
const double GAMESCENE_OUTRO_TIME = 6.0;

// ゲームシーンのステップ
enum class GameSceneStep
{
	Intro,	// 導入 フェードアウトやカウントダウン
	Fight,	// 戦闘 決着がつくまで
	Outro,	// 終了 機体の撃墜演出や余韻的演出
	Count,	// ステート数
};

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene : public SceneBase
{
public:
	// コンストラクタ
	GameScene(PlayerSettings* pl1_set, PlayerSettings* pl2_set, GameInput* pl1_input, GameInput* pl2_input)
		: player1Settings(pl1_set), player2Settings(pl2_set), player1Input(pl1_input), player2Input(pl2_input) {};

	// デストラクタ
	~GameScene() = default;

	// シーンの初期化
	void Initialize() override;

	// シーンの処理実行
	void Execute() override;

	// シーンの終了
	// 戻り値として次のシーンを返す
	SceneType Terminate() override;

private:
	// プレイヤー設定
	PlayerSettings* player1Settings;
	PlayerSettings* player2Settings;

	// プレイヤーの入力
	GameInput* player1Input;
	GameInput* player2Input;

	// 機体データ
	Hangar* hangar{};

	// プレイヤー
	Player* player1{};
	Player* player2{};

	// 地形
	Terrain* terrain{};

	// ゲームの進行状態
	GameSceneStep currentStep = GameSceneStep::Intro();

	// ゲームシーンの開始時間(sec)
	double startTime = ((double)GetNowCount() / 1000.0);

	// ステップの経過時間(sec)
	double stepTimer = 0.0;

	// 導入
	GameSceneStep Intro();

	// 対戦
	GameSceneStep Fight();

	// 終了
	GameSceneStep Outro();
};

#endif