#include"LoaderBase.h"
#include"EnemyLoader.h"
#include "DxLib.h"
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>

#include <fstream>
#include <iostream>

bool EnemyLoader::Load(LoadType type)
{
	switch (type)
	{
	case LoadType::EnemyStatus:
		StatusLoad();
		break;
	case LoadType::EnemyTransform:
		TransformLoad();
		break;
	default:
		break;
	}
	return true;
}

bool EnemyLoader::StatusLoad()
{
	std::ifstream ifs("../CSV/EnemyStatus.csv");
	if (!ifs.is_open())
	{
		// 読み込み失敗
		return false;
	}

	std::string line;
	// ファイルの終端まで
	while (std::getline(ifs, line))
	{
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

		m_enemyStatus.push_back(enemyStatus);
	}

	// ファイルを閉じる（デストラクタでも自動的に閉じられる）
	ifs.close();

#if 0
	short handle = FileRead_open("../CSV/Diffuser.csv");
	//short handle = FileRead_open("../CSV/EnemyStatus.csv");

	if (handle == 0)
	{
		FileRead_close(handle);
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

		m_enemyStatus.push_back(enemyStatus);
	}

	FileRead_close(handle);

	return true;
#endif
}

bool EnemyLoader::TransformLoad()
{
	std::ifstream ifs("../CSV/EnemysTransform.csv");
	if (!ifs.is_open())
	{
		// 読み込み失敗
		return false;
	}
	std::string line;
	// ファイルの終端まで
	while (std::getline(ifs, line))
	{
		std::stringstream trSS(line);
		std::string tokenTr;

		EnemyTransform enemyTrans;

		// 敵種類判別
		std::getline(trSS, tokenTr, ',');
		short enemyID = StringToInt(tokenTr);

		// 敵個体判別
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

		m_enemyTransform.push_back(enemyTrans);

	}

	// ファイルを閉じる（デストラクタでも自動的に閉じられる）
	ifs.close();

	return true;
#if 0
	printfDx("座標読み込み\n");
	short handleTr = FileRead_open("../CSV/EnemysTransform.csv");

	if (handleTr == 0)
	{
		FileRead_close(handleTr);
		// 読み込み失敗
		return false;
	}

	char bufferTr[256];

	// ファイルの終端まで
	while (FileRead_eof(handleTr) == 0)
	{
		FileRead_gets(bufferTr, sizeof(bufferTr), handleTr);

		std::string line = bufferTr;
		std::stringstream trSS(line);
		std::string tokenTr;

		EnemyTransform enemyTrans;

		// 敵種類判別
		std::getline(trSS, tokenTr, ',');
		short enemyID = StringToInt(tokenTr);
		printfDx("%d", enemyID);

		// 敵個体判別
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

		m_enemyTransform.push_back(enemyTrans);
	}

	FileRead_close(handleTr);

	return true;
#endif
}

int EnemyLoader::GetTypeCount()
{
	return m_enemyStatus.size();
}

int EnemyLoader::GetInstanceCount()
{
	return m_enemyTransform.size();
}

//EnemyStatus EnemyLoader::GetStatus(short id){}

//EnemyTransform EnemyLoader::GetTransform(short id){}