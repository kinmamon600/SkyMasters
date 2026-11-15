#pragma once
#include "../Component.h"
#include "../ComponentUpdateOrder.h"
#include "FighterData.h"
#include "FighterDataLoader.h"

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

	// 必要なパラメータ群
	float speed = 2000.0f;					// 前に進む速度 ブーストとかエアブレーキのときはコレを変更

	float pitchAngularVelocity = 1.2f;		// ピッチ角速度
	float pitchAngleMax = 45.0f;			// 最大ピッチ角

	float yawAngularVelocity = 1.0f;		// ヨー角速度
	float yawSlopeAngleMax = 50.0f;			// ヨーの時どのくらい傾くか

	float yawSlopeAngleSpeedMax = 100.0f;	// 傾く角速度の最大値
	float yawSlopeAngleSpeedMin = 10.0f;	// 傾く角速度の最小値

	// 処理用の変数群
	float yawSlopeAngle = 0.0f;				// 現状どのくらい傾いているか

private:
	PlayerState m_currentState = PlayerState::Manual;

	FighterStatus m_status{};

	FighterDataLoader m_loader;

	// 自身を映すカメラ
	Actor* p_myCamera;
};