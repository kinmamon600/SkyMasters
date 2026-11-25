// ライブラリ・ヘッダ
#include "FightObserver.h"

// 通知を受け取る
void FightObserver::OnNotify(EventList event)
{
	// イベントによって分岐
	switch (event)
	{
	case EventList::FighterDead:
		--m_alivePlayersNum;

		// 全機撃墜されたらゲームオーバー
		if (m_alivePlayersNum == 0)
		{
			printfDx("ゲームオーバー\n");
		}
		break;

	case EventList::EnemyDead:
		++m_defeatedEnemiesNum;

		// 全機撃墜でクリア
		if (m_defeatedEnemiesNum == m_defeatEnemiesNum)
		{
			printfDx("クリア！\n");
		}
		break;

	default:
		break;
	}
}
