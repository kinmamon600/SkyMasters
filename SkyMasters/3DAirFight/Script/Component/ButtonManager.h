#pragma once
#include"../Actor/Actor.h"
#include"Component.h"
#include"ComponentUpdateOrder.h"
#include"Input.h"
#include"../Scene/SceneBase.h"

class ButtonManager : public Component
{
public:
	ButtonManager(Actor* owner,SceneBase* base)
		:Component(owner, static_cast<int>(ComponentUpdateOrder::Behaviour)) {sb = base;};

	void Update()override;

	enum TitleButtonType
	{
		Start,      // ゲームスタート
		End,        // ゲームエンド
		Count,      // ボタンの数
	};

	int m_currentButton = Start;

private:
	SceneBase* sb;
};