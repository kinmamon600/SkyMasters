#pragma once
#include"CSVLoader.h"
#include"EnemyData.h"
#include<vector>

class EnemyLoader : public CSVLoader
{
public:
	EnemyLoader() {};

	bool Load(LoadType type) override;  //İŒv‚Æ‚µ‚Ä‚æ‚­‚È‚¢‚Ì‚Å¡Œãˆø”‚Íg‚í‚È‚¢‚æ‚¤‚É‚µ‚Ü‚·

private:

	bool StatusLoad();

	bool TransformLoad();

	//EnemyStatus GetStatus(short id);

	//EnemyTransform GetTransform(short id);

	std::vector<EnemyStatus> m_enemyStatus;
	std::vector<EnemyTransform> m_enemyTrans;
};