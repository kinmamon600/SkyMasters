#ifndef _CONTROLLERTYPEKEYCONFIGURATION_H
#define _CONTROLLERTYPEKEYCONFIGURATION_H

// ライブラリ・ヘッダ
#include "DxLib.h"  // https://dxlib.xsrv.jp/dxfunc.html

// Direct系コントローラのボタンインデックス
const int DIRECTINPUT_BUTTON_L = 4;
const int DIRECTINPUT_BUTTON_R = 5;
const int DIRECTINPUT_BUTTON_ZL = 6;
const int DIRECTINPUT_BUTTON_ZR = 7;
const int DIRECTINPUT_BUTTON_START = 9;
const int DIRECTINPUT_BUTTON_SELECT = 8;

/// <summary>
/// コントローラ種類別のキーコンフィグ
/// 主要なコントローラ(Switch Proコントローラ等)用
/// </summary>
struct ControllerTypeKeyConfiguration
{
	int DINPUT_JOYSTATE::* leftXAxis = &DINPUT_JOYSTATE::X;		// 右スティックXのメンバ変数へのポインタ
	int DINPUT_JOYSTATE::* leftYAxis = &DINPUT_JOYSTATE::Y;		// 右スティックYのメンバ変数へのポインタ
	int DINPUT_JOYSTATE::* rightXAxis = &DINPUT_JOYSTATE::Z;	// 右スティックXのメンバ変数へのポインタ
	int DINPUT_JOYSTATE::* rightYAxis = &DINPUT_JOYSTATE::Z;	// 右スティックYのメンバ変数へのポインタ

	unsigned int northIdx = 0;									// 北側ボタンの添え字
	unsigned int eastIdx = 0;									// 東側ボタンの添え字
	unsigned int southIdx = 0;									// 南側ボタンの添え字
	unsigned int westIdx = 0;									// 西側ボタンの添え字

	unsigned int lIdx = DIRECTINPUT_BUTTON_L;					// Lボタンの添え字
	unsigned int rIdx = DIRECTINPUT_BUTTON_R;					// Rボタンの添え字
	unsigned int zlIdx = DIRECTINPUT_BUTTON_ZL;					// ZLボタンの添え字
	unsigned int zrIdx = DIRECTINPUT_BUTTON_ZR;					// ZRボタンの添え字
};

// コントローラ種類別のキーコンフィグ設定
namespace CtrlTypeKeyCon
{
	// PS3(DualShock)
	// 未確認 確認済のPS4(DualShock)と共通設定
	constexpr ControllerTypeKeyConfiguration DUAL_SHOCK_3
		= { &DINPUT_JOYSTATE::X, &DINPUT_JOYSTATE::Y, &DINPUT_JOYSTATE::Z, &DINPUT_JOYSTATE::Rz, 
			3, 2, 1, 0,
			DIRECTINPUT_BUTTON_L, DIRECTINPUT_BUTTON_R, DIRECTINPUT_BUTTON_ZL, DIRECTINPUT_BUTTON_ZR };

	// PS4(DualShock)
	constexpr ControllerTypeKeyConfiguration DUAL_SHOCK_4
		= { &DINPUT_JOYSTATE::X, &DINPUT_JOYSTATE::Y, &DINPUT_JOYSTATE::Z, &DINPUT_JOYSTATE::Rz, 
			3, 2, 1, 0,
			DIRECTINPUT_BUTTON_L, DIRECTINPUT_BUTTON_R, DIRECTINPUT_BUTTON_ZL, DIRECTINPUT_BUTTON_ZR };

	// PS5(DualSense)
	// 未確認 確認済のPS4(DualShock)と共通設定
	constexpr ControllerTypeKeyConfiguration DUAL_SENSE
		= { &DINPUT_JOYSTATE::X, &DINPUT_JOYSTATE::Y, &DINPUT_JOYSTATE::Z, &DINPUT_JOYSTATE::Rz,
			3, 2, 1, 0,
			DIRECTINPUT_BUTTON_L, DIRECTINPUT_BUTTON_R, DIRECTINPUT_BUTTON_ZL, DIRECTINPUT_BUTTON_ZR };

	// JoyCon(L)
	// 未確認
	constexpr ControllerTypeKeyConfiguration SWITCH_JOY_CON_L
		= { &DINPUT_JOYSTATE::X, &DINPUT_JOYSTATE::Y, &DINPUT_JOYSTATE::Z, &DINPUT_JOYSTATE::Z, 
			0, 0, 0, 0,
			DIRECTINPUT_BUTTON_L, DIRECTINPUT_BUTTON_R, DIRECTINPUT_BUTTON_ZL, DIRECTINPUT_BUTTON_ZR };

	// JoyCon(R)
	// 未確認
	constexpr ControllerTypeKeyConfiguration SWITCH_JOY_CON_R
		= { &DINPUT_JOYSTATE::X, &DINPUT_JOYSTATE::Y, &DINPUT_JOYSTATE::Z, &DINPUT_JOYSTATE::Z, 
			0, 0, 0, 0,
			DIRECTINPUT_BUTTON_L, DIRECTINPUT_BUTTON_R, DIRECTINPUT_BUTTON_ZL, DIRECTINPUT_BUTTON_ZR };

	// Switch ProCon
	constexpr ControllerTypeKeyConfiguration SWITCH_PRO_CTRL
		= { &DINPUT_JOYSTATE::X, &DINPUT_JOYSTATE::Y, &DINPUT_JOYSTATE::Rx, &DINPUT_JOYSTATE::Ry, 
			2, 0, 1, 3,
			DIRECTINPUT_BUTTON_L, DIRECTINPUT_BUTTON_R, DIRECTINPUT_BUTTON_ZL, DIRECTINPUT_BUTTON_ZR };

	// Switch HORICon
	// 未確認 確認済のSwitch ProConと共通設定
	constexpr ControllerTypeKeyConfiguration SWITCH_HORI_PAD
		= { &DINPUT_JOYSTATE::X, &DINPUT_JOYSTATE::Y, &DINPUT_JOYSTATE::Rx, &DINPUT_JOYSTATE::Ry,
			2, 0, 1, 3,
			DIRECTINPUT_BUTTON_L, DIRECTINPUT_BUTTON_R, DIRECTINPUT_BUTTON_ZL, DIRECTINPUT_BUTTON_ZR };

	// その他
	// 未確定 教室のコントローラを基準に設定
	constexpr ControllerTypeKeyConfiguration OTHER
		= { &DINPUT_JOYSTATE::X, &DINPUT_JOYSTATE::Y, &DINPUT_JOYSTATE::Z, &DINPUT_JOYSTATE::Rz,
			1, 3, 2, 0,
			DIRECTINPUT_BUTTON_L, DIRECTINPUT_BUTTON_R, DIRECTINPUT_BUTTON_ZL, DIRECTINPUT_BUTTON_ZR };
}

#endif