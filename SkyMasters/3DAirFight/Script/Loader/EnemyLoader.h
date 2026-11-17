#pragma once
#include"EnemyData.h"
#include<vector>

class EnemyLoader
{
public:
	EnemyLoader();

	bool StatusLoad();

	bool TransformLoad();

	EnemyStatus GetStatus(short id);

	EnemyTransform GetTransform();

private:
	std::vector<EnemyStatus> m_enemyStatus;
	std::vector<EnemyTransform> m_enemyTrans;
};
