// ライブラリ・ヘッダ
#include "EnemyBase.h"
#include "../../Component/Sound.h"

// コンストラクタ
EnemyBase::EnemyBase(Actor* owner,int hp,int atk)
	:Behavior(owner)
{
	m_hp = hp;
	m_attack = atk;
}

// デストラクタ
EnemyBase::~EnemyBase()
{
	Notify(EventList::EnemyDead);
}

// 更新処理
void EnemyBase::Update()
{

}

// コライダーがアタッチされている時、接触時に呼ばれる
void EnemyBase::IsContact(Actor* other)
{
	if (other->GetLayer() == ActorLayer::PlayerBullet)
	{
		other->SetState(Actor::EDead);

		m_hp -= 25;

		if (m_hp <= 0)
		{
			m_owner->SetState(Actor::EDead);

			Sound* se = m_owner->GetComponent<Sound>();
			se->PlaySE(SE::Enemy_Explosion);
		}
	}
}
