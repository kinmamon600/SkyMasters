#ifndef _FONTHANDLE_H
#define _FONTHANDLE_H

// ライブラリ・ヘッダ
#include <string>

#include "DxLib.h"  // https://dxlib.xsrv.jp/dxfunc.html

// 使用フォント名
const std::string FONT_NAME = "Meiryo UI";

// 使用フォントハンドルの取得
int GetSmallFontHandle();
int GetMediumFontHandle();
int GetLargeFontHandle();

#endif