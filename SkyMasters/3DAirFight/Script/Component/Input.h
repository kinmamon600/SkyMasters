#ifndef _INPUT_H
#define _INPUT_H

// ライブラリ・ヘッダ
#include <DxLib.h>
#include "Component.h"
#include "ComponentUpdateOrder.h"

/// <summary>
/// 入力取得コンポーネント
/// </summary>
class Input : public Component
{
public:
	// プレイヤー番号
	enum PlayerNum
	{
		P1 = 0,
		P2 = 1,
		P3 = 2,
		P4 = 3,
	};

	// ボタン名
	enum Button
	{
		NORTH	=  0,
		EAST	=  1,
		SOUTH	=  2,
		WEST	=  3,

		L		=  4,
		R		=  5,
		ZL		=  6,
		ZR		=  7,

		START	=  8,
		SELECT	=  9,

		UP		= 10,
		DOWN	= 11,
		LEFT	= 12,
		RIGHT	= 13,
	};

	// アナログ入力名
	enum Analog
	{
		LX = 0,
		LY = 1,

		RX = 2,
		RY = 3,

		AX = 4,
		AY = 5,
	};

	// コンストラクタ
	Input(Actor* owner)
		:Component(owner, static_cast<int>(ComponentUpdateOrder::Input)) {};

	// デストラクタ
	~Input() {};

	// 取得する入力のプレイヤー番号の設定
	void SetPlayerNum(PlayerNum player_num);

	// ボタン入力の取得
	bool GetButton(Button button) const;

	// ボタン入力の取得 (押したとき)
	bool GetButtonDown(Button button) const;

	// ボタン入力の取得 (離したとき)
	bool GetButtonUp(Button button) const;

	// アナログ入力の取得
	int GetAnalog(Analog analog) const;

private:
	// このコンポーネントで取得する入力のプレイヤー番号
	PlayerNum m_playerNum = PlayerNum::P1;
};

#endif