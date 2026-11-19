// ライブラリ・ヘッダ
#include "PhysicsCollider.h"
#include "SuperDxPhysics.h"
#include "../Actor/Actor.h"
#include "Transform.h"

// コンストラクタ
PhysicsCollider::PhysicsCollider(Actor* owner)
	:Component(owner, static_cast<int>(ComponentUpdateOrder::PhysicsCollider))
{

}

// デストラクタ
PhysicsCollider::~PhysicsCollider()
{
	//RemoveComponentにコレ↓書くべきなのよね
	//SDP::DestroyPhysicalObject(m_sdpID);
}

// 更新処理
void PhysicsCollider::Update()
{
	// 自身がアタッチされているアクターのトランスフォームを取得
	Transform* owner_tr = m_owner->GetComponent<Transform>();

	// トランスフォームを更新
	if (owner_tr != nullptr)
	{
		//owner_tr->SetPosition(SDP::GetPosition(m_sdpID));
		//owner_tr->SetRotation(SDP::GetRotate(m_sdpID));
		owner_tr->SetMatrix(SDP::GetMatrix(m_sdpID));
	}
}

// 座標取得
VECTOR PhysicsCollider::GetPosition()
{
	return SDP::GetPosition(m_sdpID);
}

// 回転取得
VECTOR PhysicsCollider::GetRotate()
{
	return SDP::GetRotate(m_sdpID);
}

// 向き取得
VECTOR PhysicsCollider::GetDirection(const VECTOR& std_vec)
{
	return SDP::GetDirection(m_sdpID, std_vec);
}

// 速度設定
void PhysicsCollider::SetLinerVelocity(const VECTOR& vec)
{
	SDP::SetLinerVelocity(m_sdpID, vec);
}

void PhysicsCollider::SetAngularVelocity(const VECTOR& vec)
{
	SDP::SetAngularVelocity(m_sdpID, vec);
}

// 速度取得
VECTOR PhysicsCollider::GetLinerVelocity()
{
	return SDP::GetLinerVelocity(m_sdpID);
}

VECTOR PhysicsCollider::GetAngularVelocity()
{
	return SDP::GetAngularVelocity(m_sdpID);
}

// 質量・逆質量設定
void PhysicsCollider::SetMass(float mass)
{
	SDP::SetMass(m_sdpID, mass);
}

void PhysicsCollider::SetMassInv(float inv_mass)
{
	SDP::SetMassInv(m_sdpID, inv_mass);
}

// 質量・逆質量取得
float PhysicsCollider::GetMass()
{
	return SDP::GetMass(m_sdpID);
}

float PhysicsCollider::GetMassInv()
{
	return SDP::GetMassInv(m_sdpID);
}

// 摩擦設定
void PhysicsCollider::SetFriction(float fric)
{
	SDP::SetFriction(m_sdpID, fric);
}

// 摩擦取得
float PhysicsCollider::GetFriction()
{
	return SDP::GetFriction(m_sdpID);
}

// 反発係数設定
void PhysicsCollider::SetRestitution(float elastic)
{
	SDP::SetRestitution(m_sdpID, elastic);
}

// 反発係数取得
float PhysicsCollider::GetRestitution()
{
	return SDP::GetRestitution(m_sdpID);
}

// SDP上のオブジェクトIDの取得
int PhysicsCollider::GetID() const
{
	return m_sdpID;
}

// トランスフォームの設定(初期設定用)
void PhysicsCollider::SetTransform()
{
	// トランスフォームの取得
	Transform* tr = m_owner->GetComponent<Transform>();
	if (tr == nullptr) { return; }

	// SDPの座標・回転設定
	SDP::SetPosition(m_sdpID, tr->GetPosition());
	SDP::SetRotate(m_sdpID, tr->GetRotation());
}
