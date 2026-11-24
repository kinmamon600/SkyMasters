#ifndef _FIGHTOBSERVER_H
#define _FIGHTOBSERVER_H

// ライブラリ・ヘッダ
#include "../Component/Behavior.h"

// 前方宣言
class Actor;

/// <summary>
/// 戦闘を監視するクラス
/// </summary>
class FightObserver : public Behavior
{
public:
	// コンストラクタ
	FightObserver(Actor* owner, unsigned short player_num)
		: Behavior(owner), m_playerNum(player_num) {};

	// デストラクタ
	~FightObserver() {};

	// 通知を受け取る
	void OnNotify(EventList event) override;

private:
	// プレイヤー人数
	unsigned short m_playerNum;
};

#endif