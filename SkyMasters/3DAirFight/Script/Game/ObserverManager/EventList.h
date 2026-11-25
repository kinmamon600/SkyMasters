#ifndef _EVENTLIST_H
#define _EVENTLIST_H

/// <summary>
/// イベントリスト
/// </summary>
enum class EventList
{
	IncController,	// コントローラ数の増加
	DecController,	// コントローラ数の減少

	FighterDead,	// 自機の死亡
	EnemyDead,		// 倒すべき敵の死亡
	Count,			// イベント数
};

#endif