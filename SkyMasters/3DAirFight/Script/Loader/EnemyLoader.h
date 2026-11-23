#pragma once
#include"CSVLoader.h"
#include"EnemyData.h"
#include<vector>

class EnemyLoader : public CSVLoader
{
public:
	EnemyLoader() {};

	bool Load(LoadType type);// override;  //İŒv‚Æ‚µ‚Ä‚æ‚­‚È‚¢‚Ì‚Å¡Œãˆø”‚Íg‚í‚È‚¢‚æ‚¤‚É‚µ‚Ü‚·

	bool StatusLoad();

	bool TransformLoad();

	int GetTypeCount();
	int GetInstanceCount();

	std::vector<EnemyStatus> m_enemyStatus;
	std::vector<EnemyTransform> m_enemyTransform;
private:


	//EnemyStatus GetStatus(short id);

	//EnemyTransform GetTransform(short id);

};