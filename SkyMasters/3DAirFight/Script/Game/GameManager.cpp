#include "GameManager.h"

void GameManager::SetFighterPartsID(const FighterPartsID& id)
{
    m_fighterPartsID = id;
}

FighterPartsID GameManager::GetFighterPartsID() const
{
    return m_fighterPartsID;
}