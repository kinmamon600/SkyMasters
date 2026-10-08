// ライブラリ・ヘッダ
#include "Sky.h"
#include "Player.h"

unsigned int GetSkyColor(float y_pos)
{
	// Y座標に合わせて色を変化
	if (y_pos > COMBAT_AREA)
	{
		return GetColor(SKY_COLOR_HIGH_R, SKY_COLOR_HIGH_G, SKY_COLOR_HIGH_B);
	}
	else if (y_pos < -COMBAT_AREA)
	{
		return GetColor(SKY_COLOR_LOW_R, SKY_COLOR_LOW_G, SKY_COLOR_LOW_B);
	}
	else
	{
		y_pos += (double)COMBAT_AREA;
		unsigned short r = (unsigned short)(((float)SKY_COLOR_RANGE_R / ((float)COMBAT_AREA * 2.0f)) * y_pos) + SKY_COLOR_BASE_R;
		unsigned short g = (unsigned short)(((float)SKY_COLOR_RANGE_G / ((float)COMBAT_AREA * 2.0f)) * y_pos) + SKY_COLOR_BASE_G;
		unsigned short b = (unsigned short)(((float)SKY_COLOR_RANGE_B / ((float)COMBAT_AREA * 2.0f)) * y_pos) + SKY_COLOR_BASE_B;
		return GetColor(r, g, b);
	}
}
