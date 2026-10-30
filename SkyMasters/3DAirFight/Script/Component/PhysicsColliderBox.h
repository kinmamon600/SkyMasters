#ifndef _PHYSICSCOLLIDERBOX_H
#define _PHYSICSCOLLIDERBOX_H

// ライブラリ・ヘッダ
#include "PhysicsCollider.h"
#include "SuperDxPhysics.h"

/// <summary>
/// 物理コライダー[ボックス]
/// コンポーネントを継承したPhysicsColliderの派生クラス
/// </summary>
class PhysicsColliderBox : public PhysicsCollider
{
public:
	// コンストラクタ
	PhysicsColliderBox(Actor* owner, const VECTOR& pos, const VECTOR& size, PhysicsCollider::MotionType type, float mass);

	// デストラクタ
	~PhysicsColliderBox() {};

private:

};

#endif