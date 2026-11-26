#pragma once
#include "../Component.h"
#include "../Behavior.h"
#include "../../Loader/FighterData.h"
#include"../../Loader/FighterDataLoader.h"

class Fighter : public Behavior
{
public:
	// コンストラクタ
	Fighter(Actor* owner, unsigned short pl_num, MATRIX mat, int beam, int reticle);

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
	void Update() override;

	// 当たり判定
	void IsContact(Actor* other) override;

	// 通知を受け取る
	void OnNotify(EventList event) override;

	// ステートの変更
	void ChangeState(PlayerState state);

	// 飛行用パラメータ群
	float m_maxSpeed = 500.0f;							// 最高速度
	float m_defaultSpeed = 300.0f;						// 通常速度
	float m_minSpeed = 130.0f;							// 最低速度

	float m_acceleration = 500.0f;						// 加速度
	float m_deceleration = 500.0f;						// 減速度

	const float m_pitchAngularVelocity = 1.2f;			// ピッチ角速度
	const float m_pitchAngleMax = 25.0f;				// 最大ピッチ角

	const float m_yawAngularVelocity = 0.7f;			// ヨー角速度
	const float m_yawSlopeAngleMax = 60.0f;				// ヨーの時どのくらい傾くか

	const float m_rollAngularVelocityMax = 8.0f;		// 最大ロール角速度(ターン用)
	const float m_rollAngularVelocityMin = 0.25f;		// 最小ロール角速度(ターン用)

	const float m_yawSlopeAngleSpeedMax = 100.0f;		// 傾く角速度の最大値
	const float m_yawSlopeAngleSpeedMin = 50.0f;		// 傾く角速度の最小値

	// カメラ用パラメータ群
	VECTOR m_dispAreaMin = VGet(0.0f, 0.0f, 0.0f);		// 画面専有範囲
	VECTOR m_dispAreaMax = VGet(0.0f, 0.0f, 0.0f);

	VECTOR m_dispCenter = VGet(0.0f, 0.0f, 0.0f);		// 画面中心

	const float m_cameraFixationOffset = 80.0f;			// 注視点のオフセット
	const float m_cameraDefaultPitchAngle = 4.0f;		// ニュートラル時のカメラ傾き
	const float m_cameraDistance = 140.0f;				// 注視点とカメラの間隔

	const float m_cameraCenterAreaX = 40.0f;			// 画面上のカメラ移動範囲X
	const float m_cameraCenterAreaY = 30.0f;			// 画面上のカメラ移動範囲Y

	const float m_cameraYawAngle = 8.75f;				// カメラのヨー方向最大角度
	const float m_cameraPitchAngle = 5.5f;				// カメラのピッチ方向最大角度

	const float m_cameraTurnDistanceX = 9.4f;			// X方向の間隔補正値
	const float m_cameraTurnDistanceY = 8.5f;			// Y方向の間隔補正値

	const float m_cameraAutomaticSpeed = 300.0f;		// オートマチック制御時のカメラ移動速度
	const float m_cameraFixationSpeed = 1.0f;			// オートマチック制御時の注視点移動速度

	// 処理用の変数群
	float m_currentSpeed = m_defaultSpeed;				// 前に進む速度 ブーストとかエアブレーキのときはコレを変更
	float m_yawSlopeAngle = 0.0f;						// 現状どのくらい傾いているか

private:
	// プレイヤー番号
	unsigned short m_playerNum = 1;

	// 現在のステート
	PlayerState m_currentState = PlayerState::Manual;

	// ヒットポイント
	int m_hp = 1000;

	// オートマチック動作の向き
	short m_automaticDirection = 0;

	// 通常攻撃弾のモデルハンドル
	int m_beamModelHandle = -1;

	// 自身を映すカメラ
	Actor* p_myCamera;

	// レティクル
	Actor* p_myReticle1;
	Actor* p_myReticle2;

	// レティクルの距離
	const float m_reticleDistance = 100.0f;

	// 死んでいるか
	bool m_dead = false;

	// 通常攻撃
	void Attack(VECTOR offset, VECTOR velocity);

	// レティクル位置の設定
	void SetRericlePos();

	// ターンの向きを取得
	short GetTurnDirection(float y);

	// 死ぬ
	void Dead();
};