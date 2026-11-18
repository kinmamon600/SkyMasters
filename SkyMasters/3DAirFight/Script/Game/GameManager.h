#pragma once
#include"../Loader/FighterPartsID.h"

class GameManager
{
public:
	GameManager(){}

	void SetFighterPartsID(const FighterPartsID& id);

	FighterPartsID GetFighterPartsID()const;

private:
	FighterPartsID m_fighterPartsID;
};
