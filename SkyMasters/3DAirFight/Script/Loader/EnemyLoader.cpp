#include"EnemyLoader.h"
#include "DxLib.h"
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>

bool EnemyLoader::StatusLoad()
{

	short handle = FileRead_open("../CSV/EnemyStatus.csv");

	if (handle== 0)
	{
		// “Ç‚İ‚İ¸”s
		return false;
	}

	char buffer[256];

	// ƒtƒ@ƒCƒ‹‚ÌI’[‚Ü‚Å
	while (FileRead_eof(handle) == 0)
	{
		FileRead_gets(buffer, sizeof(buffer), handle);

		std::string line = buffer;
		std::stringstream SS(line);
		std::string token;

		EnemyStatus enemyStatus;

		// ”»•Ê”Ô†
		std::getline(SS, token, ',');
		short id = std::stoi(token);

		// ‘Ì—Í
		std::getline(SS, token, ',');
		enemyStatus.hp = std::stoi(token);

		// UŒ‚—Í
		std::getline(SS, token, ',');
		enemyStatus.attack = std::stoi(token);

		m_enemyStatus.push_back(enemyStatus);
	}

	FileRead_close(handle);

	return true;
}


bool EnemyLoader::TransformLoad()
{

	short handleTr = FileRead_open("../CSV/EnemyTransform.csv");

	if (handleTr== 0)
	{
		// “Ç‚İ‚İ¸”s
		return false;
	}

	char bufferTr[256];

	// ƒtƒ@ƒCƒ‹‚ÌI’[‚Ü‚Å
	while (FileRead_eof(handleTr) == 0)
	{
		FileRead_gets(bufferTr, sizeof(bufferTr), handleTr);

		std::string line = bufferTr;
		std::stringstream trSS(line);
		std::string tokenTr;

		EnemyTransform enemyTrans;

		//// “Gí—Ş”»•Ê
		//std::getline(trSS, tokenTr, ',');
		//short enemyID = std::stoi(tokenTr);
		//
		//// “GŒÂ‘Ì”»•Ê
		//std::getline(trSS, tokenTr, ',');
		//short instanceID = std::stoi(tokenTr);
		//
		//// ‘Ì—Í
		//std::getline(trSS, tokenTr, ',');
		//enemyTrans. = std::stoi(tokenTr);
		//
		//// UŒ‚—Í
		//std::getline(trSS, tokenTr, ',');
		//enemyTrans.attack = std::stoi(tokenTr);
		//
		//m_enemyStatus.push_back(enemyStatus);
	}

	FileRead_close(handleTr);

	return true;
}