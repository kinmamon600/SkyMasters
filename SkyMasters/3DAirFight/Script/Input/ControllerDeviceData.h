#ifndef _CONTROLLERDEVICEDATA_H
#define _CONTROLLERDEVICEDATA_H

// ライブラリ・ヘッダ
#include "DxLib.h"  // https://dxlib.xsrv.jp/dxfunc.html

// 定数
const int GAMEPAD_NULL = -1;	// コントローラが接続されていないときの番号

/// <summary>
/// コントローラ判別用のデバイス情報保持クラス
/// </summary>
class ControllerDeviceData
{
public:
	// コンストラクタ
	ControllerDeviceData() {};

	// デストラクタ
	~ControllerDeviceData() {};

	// 入力タイプ
	enum InputType
	{
		XBOX,
		DIRECT,
		None,
	};

	// データ設定
	void SetUp(int gamepad_num);

	// コントローラ番号の設定
	void SetGamepadNum(int new_num);

	// ゲッター
	int GetGamepadNum() const;				// DxLib上での使用コントローラ番号
	unsigned int GetControllerType() const;	// コントローラの種類
	InputType GetInputType() const;			// 入力タイプ
	unsigned short GetVID() const;			// メーカー識別ID (Vendor ID)
	unsigned short GetPID() const;			// 製品識別ID (Product ID)
	GUID GetGuidInstance() const;			// コントローラのデバイスインスタンス識別GUID

private:
	// DxLib上での使用コントローラ番号
	int m_gamepadNum = GAMEPAD_NULL;

	// コントローラの種類
	unsigned int m_controllerType = DX_PADTYPE_OTHER;

	// 入力タイプ
	InputType m_inputType = InputType::None;

	// ID
	unsigned short m_vid = 0;	// メーカー識別ID (Vendor ID)
	unsigned short m_pid = 0;	// 製品識別ID (Product ID)

	// コントローラのデバイスインスタンス識別GUID
	GUID m_guidInstance{};
};

#endif