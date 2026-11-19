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
	Bullet(Actor* owner, float speed);

	// デストラクタ
	~Bullet() {}

	// 更新
	void Update() override;

	// 当たり判定
	void IsContact(const Actor* other) override;

private:
	// 弾速
	float m_speed;
};

#endif