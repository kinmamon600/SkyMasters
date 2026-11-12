#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H

// ライブラリ・ヘッダ
#include <array>

#include "DxLib.h"  // https://dxlib.xsrv.jp/dxfunc.html

// 前方宣言
class ControllerInput;
class ControllerDeviceData;

// 定数
const unsigned short PLAYER_NUM_MAX = 4;// 最大プレイヤー人数

/// <summary>
/// 入力の管理クラス
/// 実行中常駐が前提
/// </summary>
class InputManager
{
public:
	// 入力モード
	enum InputMode
	{
		Menu = 0,	// メニュー画面等用 (1Pのコントローラの入力を取る コントローラの接続・切断に対するリアクション無し)
		Game = 1,	// ゲーム画面等用　 (設定されたコントローラ数分の入力を取る コントローラの接続・切断に対するリアクション有)
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
	InputManager();

	// デストラクタ
	~InputManager();

	// 入力更新
	void Update();

	// 入力モードの設定
	void SetInputMode(InputMode mode);

	// 接続されているコントローラ数の取得
	unsigned short GetControllerNum();

	// 想定されるコントローラ数を設定
	void SetExpectedControllerNum(unsigned short num);

	// 想定されるコントローラ数を取得
	unsigned short GetExpectedControllerNum() const;

	// コントローラ入力状態の取得
	const ControllerInput* GetInput(unsigned short player) const;

	// ボタン入力の取得
	bool GetButton(unsigned short player, Button button) const;

	// ボタン入力の取得 (押したとき)
	bool GetButtonDown(unsigned short player, Button button) const;

	// ボタン入力の取得 (離したとき)
	bool GetButtonUp(unsigned short player, Button button) const;

	// アナログ入力の取得
	int GetAnalog(unsigned short player, Analog analog) const;

	// コントローラ種類の取得
	unsigned int GetController(unsigned short player) const;

	// コントローラが追加接続されたかを返す
	bool WasControllerAdded() const;

	// コントローラが切断されたかを返す
	bool WasControllerRemoved() const;

	// コントローラの接続設定画面を表示する
	void DispControllerSettingsWindow();

private:
	// 現在の入力モード
	InputMode m_inputMode = InputMode::Game;

	// コントローラの入力配列
	std::array<ControllerInput*, PLAYER_NUM_MAX> p_controllerInputs;

	// 接続されているコントローラ数
	unsigned short m_connectedControllerNum = 0;

	// 想定されるコントローラ数
	unsigned short m_expectedControllerNum = 0;

	// コントローラが追加接続されたか
	bool m_wasControllerAdded = false;

	// コントローラが切断されたか
	bool m_wasControllerRemoved = false;

	// 入力モード:メニュー時の更新処理
	void UpdateModeMenu();

	// 入力モード:ゲーム時の更新処理
	void UpdateModeGame();

	// コントローラ数の増加
	void IncrementController(int current_num);

	// コントローラ数の減少
	void DecreaseController(int current_num);

	// ２つのコントローラのデバイス情報の一致不一致を判別する
	bool IsDeviceDataEqual(ControllerDeviceData* data1, ControllerDeviceData* data2);
};

#endif