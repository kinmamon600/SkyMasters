#include"StageLoader.h"
#include "DxLib.h"
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>

bool StageLoader::Load(LoadType type)
{
	EnemyStageLoad();
}

bool StageLoader::EnemyStageLoad()
{

	short handleTr = FileRead_open("../CSV/EnemyTransform.csv");

	if (handleTr == 0)
	{
		// ì«Ç›çûÇ›é∏îs
		return false;
	}

	char bufferTr[256];

	// ÉtÉ@ÉCÉãÇÃèIí[Ç‹Ç≈
	while (FileRead_eof(handleTr) == 0)
	{
		FileRead_gets(bufferTr, sizeof(bufferTr), handleTr);

		std::string line = bufferTr;
		std::stringstream trSS(line);
		std::string tokenTr;

		EnemyTransform enemyTrans;

		// ìGéÌóﬁîªï 
		std::getline(trSS, tokenTr, ',');
		short enemyID = StringToInt(tokenTr);

		// ìGå¬ëÃîªï 
		std::getline(trSS, tokenTr, ',');
		short instanceID = StringToInt(tokenTr);

		// PosX
		std::getline(trSS, tokenTr, ',');
		enemyTrans.position.x = StringToFloat(tokenTr);

		// PosY
		std::getline(trSS, tokenTr, ',');
		enemyTrans.position.y = StringToFloat(tokenTr);

		// PosZ
		std::getline(trSS, tokenTr, ',');
		enemyTrans.position.z = StringToFloat(tokenTr);

		// RoteX
		std::getline(trSS, tokenTr, ',');
		enemyTrans.rotation.x = StringToFloat(tokenTr);

		// RoteY
		std::getline(trSS, tokenTr, ',');
		enemyTrans.rotation.y = StringToFloat(tokenTr);

		// RoteZ
		std::getline(trSS, tokenTr, ',');
		enemyTrans.rotation.z = StringToFloat(tokenTr);

		// ScaleX
		std::getline(trSS, tokenTr, ',');
		enemyTrans.scale.x = StringToFloat(tokenTr);

		// ScaleY
		std::getline(trSS, tokenTr, ',');
		float sizeY = StringToFloat(tokenTr);

		// ScaleZ
		std::getline(trSS, tokenTr, ',');
		float sizeZ = StringToFloat(tokenTr);

		//m_enemyTrans.push_back(enemyTrans);
	}

	FileRead_close(handleTr);

	return true;
}
