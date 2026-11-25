#include "EnemyBase.h"

EnemyBase::EnemyBase(Actor* owner,int hp,int atk)
	:Behavior(owner)
{
	m_hp = hp;
	m_attack = atk;
}

EnemyBase::~EnemyBase()
{
	Notify(EventList::EnemyDead);
}

void EnemyBase::Update()
{

}

void EnemyBase::IsContact(const Actor* other)
{
	if (other->GetLayer() == ActorLayer::PlayerBullet)
	{
		delete other;

		m_hp -= 25;

		if (m_hp <= 0)
		{
			delete m_owner;
		}
	}
}