#pragma once
#include "../Component.h"
#include "../ComponentUpdateOrder.h"
#include "FighterData.h"
#include "FighterDataLoader.h"

class Fighter : public Component
{
public:
	// コンストラクタ
	Fighter(Actor* owner)
		: Component(owner,static_cast<int>(ComponentUpdateOrder::Behaviour)){}

	// デストラクタ
	~Fighter(){}

	enum PlayerState
	{
		Manual,		   // マニュアル操作
		Automatic,	   // 自動操作
		Dead,		   // 死亡
	};

	// 初期化
	void Initialize();

	// 更新
	void Execute();

	// 終了
	//void Terminate();

	// ステートの変更
	void ChangeState(PlayerState state);

	//	各部品のステータスの合計を求める
	FighterStatus AddStatus(short bodyID,short wingID,short diffID,short spwID);

private:
	PlayerState m_currentState = Manual;

	FighterStatus m_status{};

	FighterDataLoader m_loader;
};