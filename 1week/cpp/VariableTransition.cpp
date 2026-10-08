// ライブラリ・ヘッダ
#include "VariableTransition.h"

float VariableTransition_QuadraticIncrease(float ratio, float min, float max)
{
	if (ratio < 0.0f) { ratio = 0.0f; }
	if (ratio > 1.0f) { ratio = 1.0f; }

	return (max - min) * ratio * ratio + min;
}

float VariableTransition_QuadraticDecrease(float ratio, float min, float max)
{
	if (ratio < 0.0f) { ratio = 0.0f; }
	if (ratio > 1.0f) { ratio = 1.0f; }

	return (min - max) * ratio * ratio + max;
}

float VariableTransition_QuadraticFluctuation(float ratio, float min, float max)
{
	if (ratio < 0.0f) { ratio = 0.0f; }
	if (ratio > 1.0f) { ratio = 1.0f; }

	return ((min - max) / 0.25f) * (ratio - 0.5f) * (ratio - 0.5f) + max;
}
