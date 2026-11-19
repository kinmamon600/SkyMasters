#pragma once
#include"../Loader/FighterPartsID.h"
#include"../Loader/FighterData.h"

class GameManager
{
public:
	GameManager(){}

	void SetFighterPartsID(const FighterPartsID& id);

	FighterPartsID GetFighterPartsID()const;

private:
	FighterPartsID m_fighterPartsID;
	FighterData m_bodyData;
	FighterData m_wingData;
	FighterData m_diffData;
};
