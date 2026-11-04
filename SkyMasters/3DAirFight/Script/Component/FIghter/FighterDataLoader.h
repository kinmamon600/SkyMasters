#pragma once
#include "../Component.h"
#include "../ComponentUpdateOrder.h"
#include "FighterData.h"
#include <vector>

class FighterDataLoader : Component
{
public:
	FighterDataLoader(Actor* owner)
		:Component(owner, static_cast<int>(ComponentUpdateOrder::Behaviour)) {}

	bool LoadBody();
	static BodyData GetBody(int id);

	bool LoadWing();
	static WingData GetWing(int id);

	bool LoadDiffuser();
	static DiffuserData GetDiffuser(int id);

	bool LoadSpecialWeapon();
	static SpecialWeaponData GetSpecialWeapon(int id);

private:
	std::vector<BodyData>m_bodyData;
	std::vector<WingData>m_wingData;
	std::vector<DiffuserData>m_diffuserData;
	std::vector<SpecialWeaponData>m_specialWeaponData;
};