// ライブラリ・ヘッダ
#include "Detector.h"
#include "../Component/Transform.h"
#include "../Component/PhysicsColliderSphere.h"

// コンストラクタ
Detector::Detector(Actor* owner, const VECTOR pos, float radius, ActorLayer target, std::function<void(Actor*)> func)
	: Behavior(owner)
{
	// トランスフォームのアタッチ
	Transform* tr = new Transform(owner);
	tr->SetPosition(pos);

	// コライダーのアタッチ
	new PhysicsColliderSphere(owner, VGet(0.0f, 0.0f, 0.0f), radius, PhysicsCollider::Trigger, 1.0f);

	// 検知対象の設定
	m_targetLayer = target;

	// 呼び出す関数のポインタ設定
	p_func = func;
}

// コライダーがアタッチされている時、接触時に呼ばれる
void Detector::IsContact(Actor* other)
{
	// 指定されたレイヤーと一致したら関数実行
	if (other->GetLayer() == m_targetLayer)
	{
		p_func(other);
	}
}
