#pragma once
#include "../Component.h"
#include "../ComponentUpdateOrder.h"
#include "../../Loader/FighterData.h"
#include"../../Loader/FighterDataLoader.h"

class Fighter : public Component
{
public:
	// コンストラクタ
	Fighter(Actor* owner, Actor* cam)
		: Component(owner,static_cast<int>(ComponentUpdateOrder::Behaviour)), p_myCamera(cam){}

	// デストラクタ
	~Fighter(){}

	enum class PlayerState
	{
		Manual,		   // マニュアル操作
		Automatic,	   // 自動操作
		Dead,		   // 死亡
	};

	// 初期化
	void Initialize();

	// 更新
	void Update()override;

	// 終了
	//void Terminate();

	// ステートの変更
	void ChangeState(PlayerState state);

	//	各部品のステータスの合計を求める
	FighterStatus AddStatus(short bodyID,short wingID,short diffID,short spwID);

private:
	PlayerState m_currentState = PlayerState::Manual;

	FighterStatus m_status{};

	FighterDataLoader m_loader;

	// 自身を映すカメラ
	Actor* p_myCamera;
};