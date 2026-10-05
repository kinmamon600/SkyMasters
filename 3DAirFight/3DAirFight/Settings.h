#ifndef _SETTINGS_H
#define _SETTINGS_H

// ライブラリ・ヘッダ
#include <string>

#include "DxLib.h"  // https://dxlib.xsrv.jp/dxfunc.html

// 定数

// ウィンドウ名
const std::string WINDOW_NAME = "SkyMasters";

// ウィンドウサイズ
const unsigned int WINDOW_SIZE_X = 1920;
const unsigned int WINDOW_SIZE_Y = 1080;

// ウィンドウの中心
const unsigned int WINDOW_CENTER_X = WINDOW_SIZE_X / 2;
const unsigned int WINDOW_CENTER_Y = WINDOW_SIZE_Y / 2;

// カラービット数
const unsigned short COLOR_BIT = 32;

// フレームレート
const unsigned short FPS = 60;

// 1フレームの長さ(ms)
const float FRAME_MS = 1000.0f / (float)FPS;

// 物理世界の大きさ
const VECTOR PHYSICS_WORLD_SIZE = VGet(5000.0f, 2000.0f, 5000.0f);

// 重力
const float GRAVITY_SCALE = -30.0f;

// 戦闘エリア(半径)
const float COMBAT_AREA = 4500.0f;

#endif