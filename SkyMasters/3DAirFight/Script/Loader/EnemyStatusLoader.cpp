#include"EnemyStatusLoader.h"
#include "DxLib.h"
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>


bool EnemyStatusLoader::Load(LoadType type)
{
	StatusLoad();
}

bool EnemyStatusLoader::StatusLoad()
{

	short handle = FileRead_open("../CSV/EnemyStatus.csv");

	if (handle == 0)
	{
		// 読み込み失敗
		return false;
	}

	char buffer[256];

	// ファイルの終端まで
	while (FileRead_eof(handle) == 0)
	{
		FileRead_gets(buffer, sizeof(buffer), handle);

		std::string line = buffer;
		std::stringstream SS(line);
		std::string token;

		EnemyStatus enemyStatus;

		// 判別番号
		std::getline(SS, token, ',');
		short id = StringToInt(token);

		// 体力
		std::getline(SS, token, ',');
		enemyStatus.hp = StringToFloat(token);

		// 攻撃力
		std::getline(SS, token, ',');
		enemyStatus.attack = StringToInt(token);

		//m_enemyStatus.push_back(enemyStatus);
	}

	FileRead_close(handle);

	return true;
}


