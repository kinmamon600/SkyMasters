// 増加:ratioが0.0でmin、1.0でmaxになる
float VariableTransition_QuadraticIncrease(float ratio, float min, float max)
{
	if (ratio < 0.0f) { ratio = 0.0f; }
	if (ratio > 1.0f) { ratio = 1.0f; }

	return (max - min) * ratio * ratio + min;
}

// 減少:ratioが0.0でmax、1.0でminになる
float VariableTransition_QuadraticDecrease(float ratio, float min, float max)
{
	if (ratio < 0.0f) { ratio = 0.0f; }
	if (ratio > 1.0f) { ratio = 1.0f; }

	return (min - max) * ratio * ratio + max;
}

// 増減:ratioが0.0でmin、0.5でmax、1.0で再びminになる
float VariableTransition_QuadraticFluctuation(float ratio, float min, float max)
{
	if (ratio < 0.0f) { ratio = 0.0f; }
	if (ratio > 1.0f) { ratio = 1.0f; }

	return ((min - max) / 0.25f) * (ratio - 0.5f) * (ratio - 0.5f) + max;
}
