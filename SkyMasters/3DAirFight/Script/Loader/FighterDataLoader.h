#pragma once
#include "FighterData.h"
#include <vector>

class FighterDataLoader
{
public:
	FighterDataLoader() {}

	// 機体の読み込み
	bool LoadBody();

	// 機体の入手
	BodyData GetBody(short id) const;

	// 翼の読み込み
	bool LoadWing();

	// 翼の入手
	WingData GetWing(short id) const;

	// ディフューザーの読み込み
	bool LoadDiffuser();

	// ディフューザーの入手
	DiffuserData GetDiffuser(short id) const;

	// スペシャル武器の読み込み
	bool LoadSpecialWeapon();

	// スペシャル武器の入手
	SpecialWeaponData GetSpecialWeapon(short id) const;

	// データの数の入手
	int GetDataNum();

private:
	std::vector<BodyData>m_bodyData;
	std::vector<WingData>m_wingData;
	std::vector<DiffuserData>m_diffuserData;
	std::vector<SpecialWeaponData>m_specialWeaponData;
};