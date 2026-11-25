#pragma once

// ライブラリ・ヘッダ
#include "../../Component/Behavior.h"
#include "../../Actor/Actor.h"

/// <summary>
/// 敵の基底クラス
/// </summary>
class EnemyBase : public Behavior
{
public:
	// コンストラクタ
	EnemyBase(Actor* owner, int hp, int atk);

	// デストラクタ
	virtual ~EnemyBase();

	// 更新処理
	void Update()override;

	// コライダーがアタッチされている時、接触時に呼ばれる
	void IsContact(Actor* other) override;

protected:
	// 自身のヒットポイント
	short m_hp;

	// 自身の攻撃力
	short m_attack;

};
