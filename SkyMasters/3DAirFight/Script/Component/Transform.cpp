// ライブラリ・ヘッダ
#include "SuperDxPhysics.h"

#include "Transform.h"
#include "PhysicsCollider.h"
#include "Actor/Actor.h"

// 座標の取得
const VECTOR& Transform::GetPosition() const
{
	return m_position;
}

// 座標のセット
void Transform::SetPosition(const VECTOR& pos)
{
	m_position = pos;

	// 物理コライダーがアタッチされていたら座標更新
	PhysicsCollider* pc = m_owner->GetComponent<PhysicsCollider>();
	if (pc == nullptr) { return; }
	SDP::SetPosition(pc->GetID(), pos);
}

// 回転の取得
const VECTOR& Transform::GetRotation() const
{
	return m_rotation;
}

// 回転のセット
void Transform::SetRotation(const VECTOR& rotation)
{
	m_rotation = rotation;

	// 物理コライダーがアタッチされていたら回転更新
	PhysicsCollider* pc = m_owner->GetComponent<PhysicsCollider>();
	if (pc == nullptr) { return; }
	SDP::SetRotate(pc->GetID(), rotation);
}

// サイズの取得
const VECTOR& Transform::GetScale() const
{
	return m_scale;
}

// サイズのセット
void Transform::SetScale(const VECTOR& scale)
{
	m_scale = scale;
}