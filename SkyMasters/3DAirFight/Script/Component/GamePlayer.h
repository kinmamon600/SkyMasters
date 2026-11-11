#pragma once
#include"Component.h"
#include"ComponentUpdateOrder.h"

class GamePlayer : public Component
{
public:
	// コンストラクタ
	GamePlayer(Actor* owner)
		:Component(owner, static_cast<int>(ComponentUpdateOrder::Behaviour)) {
	}

	~GamePlayer() {};

	void Initalize();

private:
};