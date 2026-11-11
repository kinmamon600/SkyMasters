#pragma once
#include "../Component.h"
#include "../ComponentUpdateOrder.h"
#include "FighterData.h"
#include <vector>

class FighterDataLoader
{
public:
	FighterDataLoader() {}

	bool LoadBody();
	BodyData GetBody(short id) const;

	bool LoadWing();
	WingData GetWing(short id) const;

	bool LoadDiffuser();
	DiffuserData GetDiffuser(short id) const;

	bool LoadSpecialWeapon();
	SpecialWeaponData GetSpecialWeapon(short id) const;

private:
	std::vector<BodyData>m_bodyData;
	std::vector<WingData>m_wingData;
	std::vector<DiffuserData>m_diffuserData;
	std::vector<SpecialWeaponData>m_specialWeaponData;
};