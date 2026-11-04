#ifndef _CONTROLLERUI_H
#define _CONTROLLERUI_H

// ライブラリ・ヘッダ
#include <string>
#include "DxLib.h"

// 前方宣言
class ControllerInput;

/// <summary>
/// コントローラの情報・入力状態を表示する
/// コントローラの接続設定画面用であり、コンポーネントによる描画と別
/// </summary>
class ControllerUI
{
public:
	// コンストラクタ
	ControllerUI(unsigned int x, unsigned int y, ControllerInput* input) : m_ox(x), m_oy(y), m_controllerInput(input) {};

	// デストラクタ
	~ControllerUI();

	// 入力状態の描画
	void Disp();

private:
	// 表示の原点座標
	unsigned int m_ox;
	unsigned int m_oy;

	// コントローラの入力
	ControllerInput* m_controllerInput;

	// 入力時表示色
	unsigned int m_colorOn = GetColor(255, 255, 255);

	// 非入力時表示色
	unsigned int m_colorOff = GetColor(127, 127, 127);

	// 表示エリア半径
	int m_areaRadius = 100;

	// ボタンの半径
	int m_buttonRadius = 20;

	// ボタンの色を返す
	unsigned int ButtonColor(bool button);

	// Lスティックの描画
	void DispStickL(unsigned int x, unsigned int y);

	// Rスティックの描画
	void DispStickR(unsigned int x, unsigned int y);

	// 4ボタンの描画
	void Disp4Button(unsigned int x, unsigned int y);

	// 十字キーの描画
	void DispArrow(unsigned int x, unsigned int y);

	// 個別の円形ボタンを描画
	void DispCircleButton(unsigned int x, unsigned int y, bool button);

	// 個別の四角ボタンを描画
	void DispBoxButton(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, bool button);
};

#endif