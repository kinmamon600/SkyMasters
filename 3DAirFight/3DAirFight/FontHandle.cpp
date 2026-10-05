// ライブラリ・ヘッダ
#include "FontHandle.h"

int GetSmallFontHandle()
{
	return CreateFontToHandle(FONT_NAME.c_str(), 20, -1, DX_FONTTYPE_NORMAL);
}

int GetMediumFontHandle()
{
	return CreateFontToHandle(FONT_NAME.c_str(), 40, -1, DX_FONTTYPE_ANTIALIASING_4X4);
}

int GetLargeFontHandle()
{
	return CreateFontToHandle(FONT_NAME.c_str(), 80, -1, DX_FONTTYPE_ANTIALIASING_4X4);
}
