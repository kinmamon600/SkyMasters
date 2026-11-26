#pragma once

// ライブラリ・ヘッダ
#include <memory>
#include"EnemyBase.h"

/// <summary>
/// 敵 : 砲台
/// </summary>
class Cannon : public EnemyBase
{
public:
	// コンストラクタ
	Cannon(Actor* owner, int hp, int atk, int bullet);

	// デストラクタ
	~Cannon() override;

	// 更新処理
	void Update() override;

	// コライダーがアタッチされている時、接触時に呼ばれる
	//void IsContact(const Actor* other) override;

	// プレイヤーを検知したときに呼ばれる
	void DetectPlayer(Actor* p_player);

private:
	// 検知範囲
	float m_detectionRadius = 1000.0f;

	// 自身のディテクター
	Actor* p_detector;

	// クールタイム
	float m_ct = 0.5f;

	// クールタイムのカウント開始時間
	float m_countStartTime;

	// 弾速
	float m_projectileSpeed = 800.0f;

	// 弾のモデルハンドル
	int m_bulletModelhandle;

	// 攻撃
	void Attack(Actor* target);
};
