#ifndef _AUTOMATIC_H
#define _AUTOMATIC_H

// ライブラリ・ヘッダ
#include <cmath>
#include "DxLib.h"

#include "../Component.h"
#include "../ComponentUpdateOrder.h"

/// <summary>
/// 自機のオートマチック操作
/// (ターン、きりもみ)
/// </summary>
class Automatic : public Component
{
public:
	// コンストラクタ
	Automatic(Actor* owner)
		: Component(owner, static_cast<int>(ComponentUpdateOrder::Behaviour)) {
	}

	// デストラクタ
	~Automatic() {}

	// ターン動作のステート
	enum class TurnState
	{
		SetUp,		// 機体姿勢のセットアップ
		PitchTurn,	// ピッチ方向にターン いわゆる宙返り
		RollTurn,	// ロールで姿勢をニュートラルに戻す
	};

	// ターン
	// trueの時継続
	bool Turn(float direction);

	// ターンの現在状態の取得
	TurnState GetCurrentTurnState() const;

	// ターンの進行値の取得
	float GetCurrentTurnValue() const;

private:
	// ターンの現在状態
	TurnState m_currentTurnState = Automatic::TurnState::SetUp;

	// ターンの進行値(-1.0f ~ 1.0f)
	// ステート毎に値が変わる
	float m_currentTurnValue = 0.0f;

	// 姿勢判定用の内積値を保持する用
	float m_pastTurnDot = 0.0f;

	// 機体の向きをニュートラルに戻す
	// ニュートラルになったらtrue
	bool ReturnNeutral();

	// 宙返り
	// trueの時継続
	bool PitchTurn(float turn_direction);

	// ロールしてニュートラルに戻る
	// trueの時継続
	bool RollTurn();
};

#endif