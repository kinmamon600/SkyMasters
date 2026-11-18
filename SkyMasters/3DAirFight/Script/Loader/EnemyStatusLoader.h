#pragma once
#include"EnemyData.h"
#include"CSVLoader.h"
#include<vector>

class EnemyStatusLoader : public CSVLoader
{
public:
	EnemyStatusLoader() {}

	bool Load(LoadType type)override;  //İŒv‚Æ‚µ‚Ä‚æ‚­‚È‚¢‚Ì‚Å¡Œãˆø”‚Íg‚í‚È‚¢‚æ‚¤‚É‚µ‚Ü‚·

	bool StatusLoad();

private:
};
