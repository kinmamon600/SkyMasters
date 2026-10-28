#ifndef _CONTROLLERINPUT_H
#define _CONTROLLERINPUT_H

// ライブラリ・ヘッダ
#include "DxLib.h"  // https://dxlib.xsrv.jp/dxfunc.html
#include "ControllerTypeKeyConfiguration.h"
#include "ControllerDeviceData.h"

// 定数
const int ANALOG_INPUT_MAX = 1000;	// アナログ入力(ジョイスティック)の最大値

/// <summary>
/// コントローラ入力の管理クラス
/// </summary>
class ControllerInput
{
public:
	// コンストラクタ
	ControllerInput() {};

	// デストラクタ
	~ControllerInput() {};

	// 新規セットアップ
	void SetUp(int gamepad_num);

	// コントローラ番号の設定
	void SetGamepadNum(int new_num);

	// 入力の更新
	void Update();

	// このインプットクラスを使用しないように設定
	void SetNonUse();
	
	// ゲッター (デジタル:現状)
	bool GetArrowUp() const;		// 十字キー上
	bool GetArrowRight() const;		// 十字キー右
	bool GetArrowDown() const;		// 十字キー下
	bool GetArrowLeft() const;		// 十字キー左

	bool GetNorth() const;			// 北側ボタン
	bool GetEast() const;			// 東側ボタン
	bool GetSouth() const;			// 南側ボタン
	bool GetWest() const;			// 西側ボタン

	bool GetL() const;				// Lボタン
	bool GetR() const;				// Rボタン
	bool GetZL() const;				// ZLボタン
	bool GetZR() const;				// ZRボタン

	bool GetStart() const;			// スタートボタン
	bool GetSelect() const;			// セレクトボタン

	// ゲッター (デジタル:押した瞬間)
	bool GetDownArrowUp() const;	// 十字キー上
	bool GetDownArrowRight() const;	// 十字キー右
	bool GetDownArrowDown() const;	// 十字キー下
	bool GetDownArrowLeft() const;	// 十字キー左

	bool GetDownNorth() const;		// 北側ボタン
	bool GetDownEast() const;		// 東側ボタン
	bool GetDownSouth() const;		// 南側ボタン
	bool GetDownWest() const;		// 西側ボタン

	bool GetDownL() const;			// Lボタン
	bool GetDownR() const;			// Rボタン
	bool GetDownZL() const;			// ZLボタン
	bool GetDownZR() const;			// ZRボタン

	bool GetDownStart() const;		// スタートボタン
	bool GetDownSelect() const;		// セレクトボタン

	// ゲッター (デジタル:離した瞬間)
	bool GetUpArrowUp() const;		// 十字キー上
	bool GetUpArrowRight() const;	// 十字キー右
	bool GetUpArrowDown() const;	// 十字キー下
	bool GetUpArrowLeft() const;	// 十字キー左
	
	bool GetUpNorth() const;		// 北側ボタン
	bool GetUpEast() const;			// 東側ボタン
	bool GetUpSouth() const;		// 南側ボタン
	bool GetUpWest() const;			// 西側ボタン
	
	bool GetUpL() const;			// Lボタン
	bool GetUpR() const;			// Rボタン
	bool GetUpZL() const;			// ZLボタン
	bool GetUpZR() const;			// ZRボタン
	
	bool GetUpStart() const;		// スタートボタン
	bool GetUpSelect() const;		// セレクトボタン

	// ゲッター (軸)
	// スティックは-1000 ~ 1000
	// 上 / 右がプラス
	int GetLeftX() const;			// 左スティックX
	int GetLeftY() const;			// 左スティックY
	int GetRightX() const;			// 右スティックX
	int GetRightY() const;			// 右スティックY

	int GetArrowX() const;			// 十字キーX
	int GetArrowY() const;			// 十字キーY

	// ゲッター (入力以外)
	bool GetIsUse() const;									// 使用されているか
	int GetGamePadNumber() const;							// DxLib上での使用コントローラ番号
	bool GetIsConnect() const;								// 接続状態
	unsigned int GetControllerType() const;					// コントローラの種類
	ControllerDeviceData::InputType GetInputType() const;	// 入力タイプの取得
	ControllerDeviceData GetDeviceData() const;				// コントローラのデバイス情報

private:
	// このインプットクラスが使用されているか
	bool m_isUse = false;

	// コントローラのデバイス情報
	ControllerDeviceData m_deviceData;

	// コントローラ種類別のキーコンフィグ設定
	ControllerTypeKeyConfiguration m_keyConfiguration = CtrlTypeKeyCon::OTHER;

	// 接続状態
	bool m_isConnected = false;

	// 入力 (現状)
	int m_leftX = 0;					// 左スティックX
	int m_leftY = 0;					// 左スティックY
	int m_rightX = 0;					// 右スティックX
	int m_rightY = 0;					// 右スティックY

	bool m_currentArrowUp = false;		// 十字キー上
	bool m_currentArrowRight = false;	// 十字キー右
	bool m_currentArrowDown = false;	// 十字キー下
	bool m_currentArrowLeft = false;	// 十字キー左

	bool m_currentNorth = false;		// 北側ボタン
	bool m_currentEast = false;			// 東側ボタン
	bool m_currentSouth = false;		// 南側ボタン
	bool m_currentWest = false;			// 西側ボタン

	bool m_currentL = false;			// Lボタン
	bool m_currentR = false;			// Rボタン
	bool m_currentZL = false;			// ZLボタン
	bool m_currentZR = false;			// ZRボタン

	bool m_currentStart = false;		// スタートボタン
	bool m_currentSelect = false;		// セレクトボタン

	// 入力 (1つ前)
	bool m_previousArrowUp = false;		// 十字キー上
	bool m_previousArrowRight = false;	// 十字キー右
	bool m_previousArrowDown = false;	// 十字キー下
	bool m_previousArrowLeft = false;	// 十字キー左
	
	bool m_previousNorth = false;		// 北側ボタン
	bool m_previousEast = false;		// 東側ボタン
	bool m_previousSouth = false;		// 南側ボタン
	bool m_previousWest = false;		// 西側ボタン
	
	bool m_previousL = false;			// Lボタン
	bool m_previousR = false;			// Rボタン
	bool m_previousZL = false;			// ZLボタン
	bool m_previousZR = false;			// ZRボタン
	
	bool m_previousStart = false;		// スタートボタン
	bool m_previousSelect = false;		// セレクトボタン

	// コントローラ番号の更新(コントローラ数が変化した場合に実行)
	void UpdateControllerNumber(int new_num);

	// 入力のクリア
	void ClearInput();

	// 1つ前の入力の設定
	void SetPreviousInput();

	// XBOXコントローラとしての入力更新
	void UpdateXboxInput();

	// Directコントローラとしての入力更新
	void UpdateDirectInput();

	// XBOXコントローラのジョイスティック値のスケーリング
	int XboxThumbScale(int input_num);

	// ジョイスティックの正規化
	void JoyStickNormalization(int* p_x, int* p_y);
};

#endif