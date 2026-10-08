#ifndef _SKY_H
#define _SKY_H

// ライブラリ・ヘッダ
#include "DxLib.h"

// 定数
// 最高所の空の色
const unsigned short SKY_COLOR_HIGH_R = 5;
const unsigned short SKY_COLOR_HIGH_G = 105;
const unsigned short SKY_COLOR_HIGH_B = 230;

// 最低所の空の色
const unsigned short SKY_COLOR_LOW_R = 200;
const unsigned short SKY_COLOR_LOW_G = 245;
const unsigned short SKY_COLOR_LOW_B = 250;

// 各色の範囲
const short SKY_COLOR_RANGE_R = (short)SKY_COLOR_HIGH_R - (short)SKY_COLOR_LOW_R;
const short SKY_COLOR_RANGE_G = (short)SKY_COLOR_HIGH_G - (short)SKY_COLOR_LOW_G;
const short SKY_COLOR_RANGE_B = (short)SKY_COLOR_HIGH_B - (short)SKY_COLOR_LOW_B;

// 基準となる色
const unsigned short SKY_COLOR_BASE_R = (SKY_COLOR_RANGE_R < 0) ? SKY_COLOR_LOW_R : SKY_COLOR_HIGH_R;
const unsigned short SKY_COLOR_BASE_G = (SKY_COLOR_RANGE_G < 0) ? SKY_COLOR_LOW_G : SKY_COLOR_HIGH_G;
const unsigned short SKY_COLOR_BASE_B = (SKY_COLOR_RANGE_B < 0) ? SKY_COLOR_LOW_B : SKY_COLOR_HIGH_B;

// 関数
// Y座標から空の色を設定する
unsigned int GetSkyColor(float y_pos);

#endif