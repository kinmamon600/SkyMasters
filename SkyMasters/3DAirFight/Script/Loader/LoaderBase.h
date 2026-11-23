#pragma once
#include <string>

class LoaderBase
{
public:
	LoaderBase() {};

	enum  class LoadType
	{
		FighterBody,
		FighterWing,
		FighterDiffuser,

		EnemyStatus,
		EnemyTransform,
	};

	int StringToInt(const std::string& value);

	float StringToFloat(const std::string& value);

	//virtual bool Load(LoadType type) {}

private:

};