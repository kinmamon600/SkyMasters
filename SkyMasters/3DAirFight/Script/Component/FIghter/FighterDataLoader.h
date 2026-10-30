#pragma once
#include"../Component.h"
#include"../ComponentUpdateOrder.h"
#include"FighterData.h"

class FighterDataLoader : Component
{
public:
	FighterDataLoader(Actor* owner)
		:Component(owner, static_cast<int>(ComponentUpdateOrder::Behaviour)) {}

	static BodyData LoadBody(int id);
	static WingData LoadWing(int id);
	static DiffuserData LoadDiffuser(int id);
	static SpecialWeaponData LoadSpecialWeapon(int id);
};