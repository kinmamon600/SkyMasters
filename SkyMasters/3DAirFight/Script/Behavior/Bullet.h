#ifndef _BULLET_H
#define _BULLET_H

// ライブラリ・ヘッダ
#include "../Component/Component.h"
#include "../Component/Behavior.h"

// 前方宣言
class Actor;

/// <summary>
/// 弾の共通ビヘイビア
/// そのままでも継承しても
/// </summary>
class Bullet : public Behavior
{
public:
	// コンストラクタ
	Bullet(Actor* owner, VECTOR velocity, float acceleration);

	// デストラクタ
	~Bullet() {}

	// 更新
	void Update() override;

	// 当たり判定
	void IsContact(Actor* other) override;

protected:
	// 弾速
	VECTOR m_velocity;

private:
	// 加速度
	float m_acceleration;

	// 最高速度
	const float m_maxSpeed = 30.0f;
};

#endif