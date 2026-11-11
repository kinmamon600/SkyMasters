#include"FighterDataLoader.h"
#include "DxLib.h"
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>

// 機体の読み込み
bool FighterDataLoader::LoadBody()
{
	int bodyFileHandle = FileRead_open("../CSV/Body.csv");

	if (bodyFileHandle == 0)
	{
		// 読み込み失敗
		return false;
	}

	char bodyBuffer[256];

	// ファイルの終端まで
	while (FileRead_eof(bodyFileHandle) == 0)
	{
		FileRead_gets(bodyBuffer, sizeof(bodyBuffer), bodyFileHandle);

		std::string line = bodyBuffer;
		std::stringstream bodySS(line);
		std::string bodyToken;

		BodyData bodyData;

		// 何パーツ目か
		std::getline(bodySS, bodyToken, ',');
		short bodyCount = std::stoi(bodyToken);

		// 体力
		std::getline(bodySS, bodyToken, ',');
		bodyData.hp = std::stoi(bodyToken);

		// 回転速度
		std::getline(bodySS, bodyToken, ',');
		bodyData.rotateSpeed = std::stoi(bodyToken);

		// 加速度
		std::getline(bodySS, bodyToken, ',');
		bodyData.accele = std::stoi(bodyToken);

		// 通常攻撃力
		std::getline(bodySS, bodyToken, ',');
		bodyData.attackPower = std::stoi(bodyToken);

		m_bodyData.push_back(bodyData);

		//printfDx("ボディ\n何パーツ目か:%d\n", bodyCount);
		//printfDx("体力:%d\n", bodyData.hp);
		//printfDx("回転速度:%f\n", bodyData.rotateSpeed);
		//printfDx("加速度:%d\n", bodyData.accele);
		//printfDx("通常攻撃力:%d\n\n", bodyData.attackPower);
	}

	FileRead_close(bodyFileHandle);

	return true;
}

// 翼の読み込み
bool FighterDataLoader::LoadWing()
{
	int wingfFileHandle = FileRead_open("../CSV/Wing.csv");

	if (wingfFileHandle == 0)
	{
		// 読み込み失敗
		return false;
	}

	char wingBuffer[256];

	// ファイルの終端まで
	while (FileRead_eof(wingfFileHandle) == 0)
	{
		FileRead_gets(wingBuffer, sizeof(wingBuffer), wingfFileHandle);

		std::string line = wingBuffer;
		std::stringstream wingSS(line);
		std::string wingToken;

		WingData wingData;

		// 何パーツ目か
		std::getline(wingSS, wingToken, ',');
		short wingCount = std::stoi(wingToken);

		// 体力
		std::getline(wingSS, wingToken, ',');
		wingData.hp = std::stoi(wingToken);

		// 回転速度
		std::getline(wingSS, wingToken, ',');
		wingData.rotateSpeed = std::stoi(wingToken);

		// 加速度
		std::getline(wingSS, wingToken, ',');
		wingData.accele = std::stoi(wingToken);

		m_wingData.push_back(wingData);

		//printfDx("翼\n何パーツ目か:%d\n", wingCount);
		//printfDx("体力:%d\n", wingData.hp);
		//printfDx("回転速度:%f\n", wingData.rotateSpeed);
		//printfDx("加速度:%d\n\n", wingData.accele);
	}

	FileRead_close(wingfFileHandle);

	return true;
}

// ディフューザーの読み込み
bool FighterDataLoader::LoadDiffuser()
{
	int diffFileHandle = FileRead_open("../CSV/Diffuser.csv");

	if (diffFileHandle == 0)
	{
		// 読み込み失敗
		return false;
	}

	char diffBuffer[256];

	// ファイルの終端まで
	while (FileRead_eof(diffFileHandle) == 0)
	{
		FileRead_gets(diffBuffer, sizeof(diffBuffer), diffFileHandle);

		std::string line = diffBuffer;
		std::stringstream diffSS(line);
		std::string diffToken;

		DiffuserData diffData;

		// 何パーツ目か
		std::getline(diffSS, diffToken, ',');
		short diffCount = std::stoi(diffToken);

		// 体力
		std::getline(diffSS, diffToken, ',');
		diffData.hp = std::stoi(diffToken);

		// 回転速度
		std::getline(diffSS, diffToken, ',');
		diffData.rotateSpeed = std::stoi(diffToken);

		// 加速度
		std::getline(diffSS, diffToken, ',');
		diffData.accele = std::stoi(diffToken);

		m_diffuserData.push_back(diffData);

		//printfDx("ディフューザー\n何パーツ目か:%d\n", diffCount);
		//printfDx("体力:%d\n", diffData.hp);
		//printfDx("回転速度:%f\n", diffData.rotateSpeed);
		//printfDx("加速度:%d\n\n", diffData.accele);
	}

	FileRead_close(diffFileHandle);

	return true;
}

// スペシャル武器の読み込み
bool FighterDataLoader::LoadSpecialWeapon()
{
	int spwFileHandle = FileRead_open("SpecialWeapon.csv");

	if (spwFileHandle == 0)
	{
		// 読み込み失敗
		return false;
	}

	char spwBuffer[256];

	// ファイルの終端まで
	while (FileRead_eof(spwFileHandle) == 0)
	{
		FileRead_gets(spwBuffer, sizeof(spwBuffer), spwFileHandle);

		std::string line = spwBuffer;
		std::stringstream spwSS(line);
		std::string bodyToken;

		SpecialWeaponData spwData;

		//何パーツ目か
		std::getline(spwSS, bodyToken, ',');
		short spwCount = std::stoi(bodyToken);

		// スペシャル攻撃力
		std::getline(spwSS, bodyToken, ',');
		spwData.specialAttack = std::stoi(bodyToken);

		m_specialWeaponData.push_back(spwData);

		printfDx("スペシャル武器\n何パーツ目か:%d\n", spwCount);
		printfDx("体力:%d\n", spwData.specialAttack);
	}

	FileRead_close(spwFileHandle);

	return true;
}

BodyData FighterDataLoader::GetBody(short id) const
{
	return m_bodyData[id];
}

WingData FighterDataLoader::GetWing(short id) const
{
	return m_wingData[id];
}

DiffuserData FighterDataLoader::GetDiffuser(short id) const
{
	return m_diffuserData[id];
}

SpecialWeaponData FighterDataLoader::GetSpecialWeapon(short id) const
{
	return m_specialWeaponData[id];
}