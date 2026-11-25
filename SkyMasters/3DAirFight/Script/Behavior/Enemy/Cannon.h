#pragma once
#include"EnemyBase.h"

class Cannon : public EnemyBase
{
public:
	Cannon(Actor* owner, int hp, int atk);

	~Cannon()override;

	void Update()override;

	void IsContact(const Actor* other)override;
private:
	// 検知範囲
	short m_detectionLength = 500;

	// クールタイム
	short m_ct = 2;
};