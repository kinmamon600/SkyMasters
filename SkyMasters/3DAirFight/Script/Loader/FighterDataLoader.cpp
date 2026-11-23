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
		FileRead_close(bodyFileHandle);
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

		//printfDx("%dパーツ目\n", bodyCount);
		//printfDx("%d\n", bodyData.hp);
		//printfDx("%d\n", bodyData.rotateSpeed);

		// 残りのデータ取得
		std::vector<std::string>bodyTransformTokens;

		while (std::getline(bodySS, bodyToken, ','))
		{
			bodyTransformTokens.push_back(bodyToken);
		}

		for (short i = 0; i + 8 < bodyTransformTokens.size(); i += 9)
		{
			// Position
			VECTOR position = VGet(
				std::stof(bodyTransformTokens[i]),
				std::stof(bodyTransformTokens[i + 1]),
				std::stof(bodyTransformTokens[i + 2])
			);

			// Rotation
			VECTOR rotation = VGet(
				std::stof(bodyTransformTokens[i + 3]),
				std::stof(bodyTransformTokens[i + 4]),
				std::stof(bodyTransformTokens[i + 5])
			);

			// Scale
			VECTOR scale = VGet(
				std::stof(bodyTransformTokens[i + 6]),
				std::stof(bodyTransformTokens[i + 7]),
				std::stof(bodyTransformTokens[i + 8])
			);

			bodyData.position.push_back(position);
			bodyData.rotation.push_back(rotation);
			bodyData.scale.push_back(scale);
		}

		m_bodyData.push_back(bodyData);

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
		FileRead_close(wingfFileHandle);
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

		// 残りのデータ取得
		std::vector<std::string>wingTransformTokens;

		while (std::getline(wingSS, wingToken, ','))
		{
			wingTransformTokens.push_back(wingToken);
		}

		for (short i = 0; i + 8 < wingTransformTokens.size(); i += 9)
		{
			// Position
			VECTOR position = VGet(
				std::stof(wingTransformTokens[i]),
				std::stof(wingTransformTokens[i + 1]),
				std::stof(wingTransformTokens[i + 2])
			);

			// Rotation
			VECTOR rotation = VGet(
				std::stof(wingTransformTokens[i + 3]),
				std::stof(wingTransformTokens[i + 4]),
				std::stof(wingTransformTokens[i + 5])
			);

			// Scale
			VECTOR scale = VGet(
				std::stof(wingTransformTokens[i + 6]),
				std::stof(wingTransformTokens[i + 7]),
				std::stof(wingTransformTokens[i + 8])
			);

			wingData.position.push_back(position);
			wingData.rotation.push_back(rotation);
			wingData.scale.push_back(scale);
		}

		m_wingData.push_back(wingData);
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
		FileRead_close(diffFileHandle);
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

		// 残りのデータ取得
		std::vector<std::string>diffTransformTokens;

		while (std::getline(diffSS, diffToken, ','))
		{
			diffTransformTokens.push_back(diffToken);
		}

		for (short i = 0; i + 8 < diffTransformTokens.size(); i += 9)
		{
			// Position
			VECTOR position = VGet(
				std::stof(diffTransformTokens[i]),
				std::stof(diffTransformTokens[i + 1]),
				std::stof(diffTransformTokens[i + 2])
			);

			// Rotation
			VECTOR rotation = VGet(
				std::stof(diffTransformTokens[i + 3]),
				std::stof(diffTransformTokens[i + 4]),
				std::stof(diffTransformTokens[i + 5])
			);

			// Scale
			VECTOR scale = VGet(
				std::stof(diffTransformTokens[i + 6]),
				std::stof(diffTransformTokens[i + 7]),
				std::stof(diffTransformTokens[i + 8])
			);

			diffData.position.push_back(position);
			diffData.rotation.push_back(rotation);
			diffData.scale.push_back(scale);
		}

		m_diffuserData.push_back(diffData);
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
		FileRead_close(spwFileHandle);
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

		//printfDx("スペシャル武器\n何パーツ目か:%d\n", spwCount);
		//printfDx("体力:%d\n", spwData.specialAttack);
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

int FighterDataLoader::GetDataNum()
{
	return m_bodyData.size();
}