// ライブラリ・ヘッダ
#include "PhysicsColliderSphere.h"
#include "SuperDxPhysics.h"

// コンストラクタ
PhysicsColliderSphere::PhysicsColliderSphere(Actor* owner, const VECTOR& pos, float radius, PhysicsCollider::MotionType type, float mass)
	: PhysicsCollider(owner)
{
	m_sdpID = SDP::CreatePhysicalSphere(pos, radius, static_cast<ePfxMotionType>(type), mass, GetColorU8(255, 255, 255, 0));
}
