#pragma once
#include "../Component.h"
#include "../ComponentUpdateOrder.h"
#include "FighterData.h"
#include "FighterDataLoader.h"

class Fighter : public Component
{
public:
	Fighter(Actor* owner,const Fighter& data)
		: Component(owner,
			static_cast<int>(ComponentUpdateOrder::Behaviour)){}

	void SetData(const FighterData& data);

private:
	FighterData m_fighterData{};

};