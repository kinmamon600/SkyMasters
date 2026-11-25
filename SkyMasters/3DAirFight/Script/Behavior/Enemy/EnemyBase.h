#pragma once
#include "../../Component/Behavior.h"
#include "../../Actor/Actor.h"

class EnemyBase : public Behavior
{
public:
	EnemyBase(Actor* owner, int hp, int atk);

	virtual ~EnemyBase();

	void Update()override;

	void IsContact(const Actor* other) override;

protected:
	short m_hp;
	short m_attack;

};