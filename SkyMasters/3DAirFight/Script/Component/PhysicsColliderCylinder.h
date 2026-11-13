#ifndef _PHYSICSCOLLIDERCYLINDER_H
#define _PHYSICSCOLLIDERCYLINDER_H

// ライブラリ・ヘッダ
#include "PhysicsCollider.h"
#include "SuperDxPhysics.h"

/// <summary>
/// 物理コライダー[筒]
/// コンポーネントを継承したPhysicsColliderの派生クラス
/// </summary>
class PhysicsColliderCylinder : public PhysicsCollider
{
public:
	// コンストラクタ
	PhysicsColliderCylinder(Actor* owner, const VECTOR& pos, float length, float radius, PhysicsCollider::MotionType type, float mass);

	// デストラクタ
	~PhysicsColliderCylinder() {};

private:

};

#endif