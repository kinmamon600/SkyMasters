// ライブラリ・ヘッダ
#include <cmath>
#include "Bullet.h"
#include "../World/WorldSettings.h"
#include "../Component/Transform.h"
#include "../Screen/Screen.h"
#include "../Actor/Actor.h"
#include "../Component/PhysicsColliderSphere.h"
#include "../Component/PhysicsColliderCylinder.h"
#include "../Game/Game.h"
#include "../Game/ObserverManager/EventList.h"

// コンストラクタ
Bullet::Bullet(Actor* owner, VECTOR velocity, float acceleration)
	:Behavior(owner)
{
	// 弾速設定
	//m_speed = speed / Screen::FPS;
	//m_speed = speed;
	//m_velocity = VScale(velocity, 1.0f / Screen::FPS);
	m_velocity = VScale(velocity, 1.0f / Screen::FPS);
	m_acceleration = acceleration / Screen::FPS;

	//ePfxMotionType::kPfxMotionTypeTrigger
	// コライダーのアタッチと設定
	new PhysicsColliderSphere(owner, VGet(0.0f, 0.0f, 0.0f), 3.0f, PhysicsCollider::Trigger, 1.0f);
	//new PhysicsColliderCylinder(owner, VGet(0.0f, 0.0f, 0.0f), 10.0f, 1.2f, PhysicsCollider::Trigger, 1.0f);
	//printfDx("アタッチされたよ\n");
}

// 更新
void Bullet::Update()
{
	//printfDx("前へ進め！\n");
	// 前進
	//PhysicsColliderSphere* pc = m_owner->GetComponent<PhysicsColliderSphere>();
	//pc->SetLinerVelocity(m_velocity);

	//VECTOR direction = pc->GetDirection(VGet(0.0f, 0.0f, -1.0f));
	//VECTOR velocity = VScale(direction, m_speed);
	//printfDx("%f, %f, %f\n", direction.x, direction.y, direction.z);

	Transform* tr = m_owner->GetComponent<Transform>();

	VECTOR pos = tr->GetPosition();

	float xz_size = std::sqrt(pos.x * pos.x + pos.z * pos.z);

	if (xz_size >= WorldSettings::WorldRadius)
	{
		m_owner->SetState(Actor::EDead);
	}

	if (abs(pos.y) >= WorldSettings::WorldLength)
	{
		m_owner->SetState(Actor::EDead);
	}

	if (m_acceleration > 0.0f && VSize(m_velocity) < m_maxSpeed)
	{
		VECTOR vec = VScale(VNorm(m_velocity), m_acceleration);
		m_velocity = VAdd(m_velocity, vec);
	}

	tr->SetPosition(VAdd(pos, m_velocity));
}

// 当たり判定
void Bullet::IsContact(Actor* other)
{
	// 地形に当たったら消去
	if (other->GetLayer() == ActorLayer::Terrain)
	{
		m_owner->SetState(Actor::EDead);
		//m_owner->GetGame()->RemoveActor(m_owner);
		//delete m_owner;
		//m_owner = nullptr;
	}
}
