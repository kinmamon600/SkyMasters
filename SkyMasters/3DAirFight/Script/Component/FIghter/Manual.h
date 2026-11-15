#pragma once
#include "../Component.h"
#include "../ComponentUpdateOrder.h"

#include <cmath>
#include "DxLib.h"

/// <summary>
/// 自機のマニュアル操作
/// </summary>
class Manual : public Component
{
public:
	// コンストラクタ
	Manual(Actor* owner)
		: Component(owner, static_cast<int>(ComponentUpdateOrder::Behaviour)) {}

	// デストラクタ
	~Manual() {}

	// マニュアル操作での機体制御
	VECTOR FighterControl();

private:
	
};
