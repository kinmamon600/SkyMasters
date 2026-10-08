#ifndef _INPUT_H
#define _INPUT_H

// ライブラリ・ヘッダ
#include "DxLib.h"  // https://dxlib.xsrv.jp/dxfunc.html

// 定数
// スティック入力の最大値・最小値
const int JOYPAD_MAX =  1000;
const int JOYPAD_MIN = -1000;

// スティックのデッドゾーン
const double JOYPAD_DEADZONE = 0.2;

class GameInput
{
private:
	// 使用コントローラ
	int gamepadNum;

	// 入力状態
	bool north;	// 北側ボタン
	bool east;	// 東側ボタン
	bool south;	// 南側ボタン
	bool west;	// 西側ボタン
	bool l;		// Lボタン
	bool r;		// Rボタン
	bool start;	// スタートボタン

	int x;		// ジョイスティックX
	int y;		// ジョイスティックY

public:
	// コンストラクタ
	GameInput() : gamepadNum(-1), north(false), east(false), south(false), west(false),
		l(false), r(false), start(false), x(0), y(0) {};

	// デストラクタ
	~GameInput() {};

	// 使用コントローラの設定
	void SetGamepad(int pad);

	// 入力状況の更新
	void Update();

	// 入力の取得
	bool GetNorth() const;
	bool GetEast() const;
	bool GetSouth() const;
	bool GetWest() const;
	bool GetL() const;
	bool GetR() const;
	//bool GetStart() const;
	int GetX() const;
	int GetY() const;
	short GetDigitalX() const;
	short GetDigitalY() const;
};

#endif