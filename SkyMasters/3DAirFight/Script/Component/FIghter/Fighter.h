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

	float rollAngularVelocity = 6.0f;		// ロール角速度(ターン用)

	float yawSlopeAngleSpeedMax = 100.0f;	// 傾く角速度の最大値
	float yawSlopeAngleSpeedMin = 10.0f;	// 傾く角速度の最小値

	float cameraFixationOffset = 550.0f;	// 注視点のオフセット
	float cameraDefaultPitchAngle = 3.0f;	// ニュートラル時のカメラ傾き
	float cameraDistance = 855.0f;			// 注視点とカメラの間隔

	float cameraCenterAreaX = 20.0f;		// 画面上のカメラ移動範囲X
	float cameraCenterAreaY = 10.0f;		// 画面上のカメラ移動範囲Y

	float cameraYawAngle = 8.75f;			// カメラのヨー方向最大角度
	float cameraPitchAngle = 5.5f;			// カメラのピッチ方向最大角度

	float cameraTurnDistanceX = 94.0f;		// X方向の間隔補正値
	float cameraTurnDistanceY = 85.0f;		// Y方向の間隔補正値

	// 処理用の変数群
	float yawSlopeAngle = 0.0f;				// 現状どのくらい傾いているか

private:
	PlayerState m_currentState = PlayerState::Manual;

	FighterStatus m_status{};

	FighterDataLoader m_loader;

	// 自身を映すカメラ
	Actor* p_myCamera;
};