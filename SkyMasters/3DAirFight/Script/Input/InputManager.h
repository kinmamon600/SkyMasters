#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H

// ライブラリ・ヘッダ
#include <array>

#include "DxLib.h"  // https://dxlib.xsrv.jp/dxfunc.html
#include "ControllerInput.h"

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
		Menu,	// メニュー画面等用 (1Pのコントローラの入力を取る コントローラの接続・切断に対するリアクション無し)
		Game,	// ゲーム画面等用　 (設定されたコントローラ数分の入力を取る コントローラの接続・切断に対するリアクション有)
	};

	// ボタン名
	enum Button
	{
		NORTH,
		EAST,
		SOUTH,
		WEST,

		L,
		R,
		ZL,
		ZR,

		START,
		SELECT,

		UP,
		DOWN,
		LEFT,
		RIGHT,
	};

	// アナログ入力名
	enum Analog
	{
		LX,
		LY,

		RX,
		RY,

		AX,
		AY,
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

private:
	// 現在の入力モード
	InputMode m_inputMode = InputMode::Menu;

	// コントローラの入力配列
	std::array<ControllerInput*, PLAYER_NUM_MAX> p_controllerInputs;

	// 接続されているコントローラ数
	unsigned short m_connectedControllerNum = 0;

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