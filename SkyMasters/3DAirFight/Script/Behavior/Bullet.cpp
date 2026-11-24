// ライブラリ・ヘッダ
#include "Bullet.h"
#include "../Component/Transform.h"
#include "../Screen/Screen.h"
#include "../Actor/Actor.h"
#include "../Component/PhysicsColliderSphere.h"

// コンストラクタ
Bullet::Bullet(Actor* owner, VECTOR velocity)
	:Behavior(owner)
{
	// 弾速設定
	//m_speed = speed / Screen::FPS;
	//m_speed = speed;
	//m_velocity = VScale(velocity, 1.0f / Screen::FPS);
	m_velocity = velocity;

	//ePfxMotionType::kPfxMotionTypeTrigger
	// コライダーのアタッチと設定
	new PhysicsColliderSphere(owner, VGet(0.0f, 0.0f, 0.0f), 1.0f, PhysicsCollider::Active, 0.1f);
	//printfDx("アタッチされたよ\n");
}

// 更新
void Bullet::Update()
{
	//printfDx("前へ進め！\n");
	// 前進
	PhysicsColliderSphere* pc = m_owner->GetComponent<PhysicsColliderSphere>();
	//VECTOR direction = pc->GetDirection(VGet(0.0f, 0.0f, -1.0f));
	//VECTOR velocity = VScale(direction, m_speed);
	//printfDx("%f, %f, %f\n", direction.x, direction.y, direction.z);
	pc->SetLinerVelocity(m_velocity);

	//Transform* tr = m_owner->GetComponent<Transform>();
	//tr->SetPosition(VAdd(tr->GetPosition(), velocity));
}

// 当たり判定
void Bullet::IsContact(const Actor* other)
{

}
