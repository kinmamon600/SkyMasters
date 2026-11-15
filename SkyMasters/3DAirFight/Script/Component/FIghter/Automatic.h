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

	// 機体の向きをニュートラルに戻す
	// ニュートラルになったらtrue
	bool ReturnNeutral();

	// ターン
	// trueの時継続
	bool Turn();

private:
	// ターン動作のステート
	enum class TurnState
	{
		SetUp,		// 機体姿勢のセットアップ
		PitchTurn,	// ピッチ方向にターン いわゆる宙返り
		RollTurn,	// ロールで姿勢をニュートラルに戻す
	};

	// ターンの現在状態
	TurnState m_currentTurnState = Automatic::TurnState::SetUp;

	// 宙返り
	// trueの時継続
	bool PitchTurn();
};

#endif