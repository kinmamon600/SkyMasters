// ライブラリ・ヘッダ
#include "Bullet.h"
#include "../Screen/Screen.h"
#include "../Actor/Actor.h"
#include "../Component/PhysicsColliderSphere.h"

// コンストラクタ
Bullet::Bullet(Actor* owner, float speed)
	:Behavior(owner)
{
	// 弾速設定
	m_speed = speed / Screen::FPS;

	// コライダーのアタッチと設定
	new PhysicsColliderSphere(owner, VGet(0.0f, 0.0f, 0.0f), 50.0f, PhysicsCollider::Trigger, 0);
	printfDx("アタッチされたよ\n");
}

// 更新
void Bullet::Update()
{
	//printfDx("前へ進め！\n");
	// 前進
	PhysicsColliderSphere* pc = m_owner->GetComponent<PhysicsColliderSphere>();
	VECTOR velocity = VScale(pc->GetDirection(VGet(0.0f, 0.0f, -1.0f)), m_speed);
	pc->SetLinerVelocity(velocity);
}

// 当たり判定
void Bullet::IsContact(const Actor* other)
{

}
