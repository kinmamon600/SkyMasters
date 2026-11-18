// ライブラリ・ヘッダ
#include "Behavior.h"
#include "SuperDxPhysics.h"
#include "PhysicsCollider.h"
#include "Actor/Actor.h"

// コライダーがアタッチされている時、接触を判定する
void Behavior::CheckContact()
{
	// コライダーがアタッチされているか確認
	PhysicsCollider* pc = m_owner->GetComponent<PhysicsCollider>();
	if (pc == nullptr) { return; }

	// IDがあるか確認
	int my_id = pc->GetID();
	if (my_id > SDP::ID_NULL) { return; }

	// 当たり判定を確認
	PfxRigidBodyWorld* rb_world = &physicsGetWorld();

	for (unsigned int i = 0; i < rb_world->getContactCount(); ++i)
	{
		const PfxContactManifold& contact = rb_world->getContactManifold(i);

		if (contact.getNumContacts() <= 0)
		{
			continue;
		}

		int id_a = contact.getRigidBodyIdA();
		int id_b = contact.getRigidBodyIdB();

		if (id_a == my_id)
		{
			//m_owner->GetGame()->
		}

		if (id_b == my_id)
		{

		}
	}
}
