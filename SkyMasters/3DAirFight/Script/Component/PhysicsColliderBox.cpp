// ライブラリ・ヘッダ
#include "PhysicsColliderBox.h"
#include "SuperDxPhysics.h"

// コンストラクタ
PhysicsColliderBox::PhysicsColliderBox(Actor* owner, const VECTOR& pos, const VECTOR& size, PhysicsCollider::MotionType type, float mass)
	: PhysicsCollider(owner)
{
	m_sdpID = SDP::CreatePhysicalBox(pos, size, static_cast<ePfxMotionType>(type), mass, GetColorU8(255, 255, 255, 0));
}
