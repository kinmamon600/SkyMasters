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

	// 必要なパラメータ群
	const float m_speed = 4000.0f;						// 前に進む速度 ブーストとかエアブレーキのときはコレを変更

	const float m_pitchAngularVelocity = 1.2f;			// ピッチ角速度
	const float m_pitchAngleMax = 45.0f;				// 最大ピッチ角

	const float m_yawAngularVelocity = 1.0f;			// ヨー角速度
	const float m_yawSlopeAngleMax = 50.0f;				// ヨーの時どのくらい傾くか

	const float m_rollAngularVelocityMax = 9.5f;		// 最大ロール角速度(ターン用)
	const float m_rollAngularVelocityMin = 1.5f;		// 最小ロール角速度(ターン用)

	const float m_yawSlopeAngleSpeedMax = 100.0f;		// 傾く角速度の最大値
	const float m_yawSlopeAngleSpeedMin = 50.0f;		// 傾く角速度の最小値

	const float m_cameraFixationOffset = 550.0f;		// 注視点のオフセット
	const float m_cameraDefaultPitchAngle = 3.0f;		// ニュートラル時のカメラ傾き
	const float m_cameraDistance = 855.0f;				// 注視点とカメラの間隔

	const float m_cameraCenterAreaX = 20.0f;			// 画面上のカメラ移動範囲X
	const float m_cameraCenterAreaY = 10.0f;			// 画面上のカメラ移動範囲Y

	const float m_cameraYawAngle = 8.75f;				// カメラのヨー方向最大角度
	const float m_cameraPitchAngle = 5.5f;				// カメラのピッチ方向最大角度

	const float m_cameraTurnDistanceX = 94.0f;			// X方向の間隔補正値
	const float m_cameraTurnDistanceY = 85.0f;			// Y方向の間隔補正値

	const float m_cameraAutomaticSpeed = 1600.0f;		// オートマチック制御時のカメラ移動速度
	const float m_cameraAutomaticFixationSpeed = 80.0f;	// オートマチック制御時の注視点移動速度

	// 処理用の変数群
	float m_yawSlopeAngle = 0.0f;					// 現状どのくらい傾いているか

private:
	PlayerState m_currentState = PlayerState::Manual;

	FighterStatus m_status{};

	FighterDataLoader m_loader;

	// ヒットポイント
	int m_hp = 1000;

	// オートマチック動作の向き
	short m_automaticDirection = 0;

	// 自身を映すカメラ
	Actor* p_myCamera;
};