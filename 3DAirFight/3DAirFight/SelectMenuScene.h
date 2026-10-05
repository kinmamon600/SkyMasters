#ifndef _SELECTMENUSCENE_H
#define _SELECTMENUSCENE_H

// ライブラリ・ヘッダ
#include "SceneDefine.h"
#include "SceneBase.h"
#include "GameInput.h"
#include "Player.h"
#include "Terrain.h"
#include "FighterColorPalette.h"

/// <summary>
/// セレクトメニューシーン
/// </summary>
class SelectMenuScene : public SceneBase
{
public:
	// コンストラクタ
	SelectMenuScene(PlayerSettings* pl1_set, PlayerSettings* pl2_set, GameInput* pl1_input, GameInput* pl2_input)
		: player1Settings(pl1_set), player2Settings(pl2_set), player1Input(pl1_input), player2Input(pl2_input) {};

	// デストラクタ
	~SelectMenuScene() = default;

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

	// 地形(背景表示用)
	Terrain* terrain{};

	// 入力可否
	bool player1CanInputX = false;

	bool player2CanInputX = false;

	bool player1CanInputL = false;
	bool player1CanInputR = false;

	bool player2CanInputL = false;
	bool player2CanInputR = false;

	bool player1CanInputDecision = false;
	bool player2CanInputDecision = false;

	// 各プレイヤーが選択しているファイターのID
	unsigned short player1FighterID = 0;
	unsigned short player2FighterID = 0;

	// 各プレイヤーが選択しているカラーパレットのID
	unsigned short player1ColorPaletteID = 0;
	unsigned short player2ColorPaletteID = 0;

	// 各プレイヤーの決定状態
	bool player1IsDecision = false;
	bool player2IsDecision = false;

	// 各プレイヤーの選択・決定
	void Player1Selection();
	void Player2Selection();
};

#endif