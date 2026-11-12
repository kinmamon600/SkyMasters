#ifndef _PHYSICSCOLLIDERSPHERE_H
#define _PHYSICSCOLLIDERSPHERE_H

// ライブラリ・ヘッダ
#include "PhysicsCollider.h"
#include "SuperDxPhysics.h"

/// <summary>
/// 物理コライダー[球]
/// コンポーネントを継承したPhysicsColliderの派生クラス
/// </summary>
class PhysicsColliderSphere : public PhysicsCollider
{
public:
	// コンストラクタ
	PhysicsColliderSphere(Actor* owner, const VECTOR& pos, float radius, PhysicsCollider::MotionType type, float mass);

	// デストラクタ
	~PhysicsColliderSphere() {};

private:

};

#endif