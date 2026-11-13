// ライブラリ・ヘッダ
#include "PhysicsColliderCylinder.h"
#include "SuperDxPhysics.h"

// コンストラクタ
PhysicsColliderCylinder::PhysicsColliderCylinder(Actor* owner, const VECTOR& pos, float length, float radius, PhysicsCollider::MotionType type, float mass)
	: PhysicsCollider(owner)
{
	m_sdpID = SDP::CreatePhysicalCylinder(pos, length, radius, static_cast<ePfxMotionType>(type), mass, GetColorU8(255, 255, 255, 0));
}
