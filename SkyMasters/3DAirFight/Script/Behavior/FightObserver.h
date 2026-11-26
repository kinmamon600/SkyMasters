#ifndef _FIGHTOBSERVER_H
#define _FIGHTOBSERVER_H

// ライブラリ・ヘッダ
#include "../Component/Behavior.h"

// 前方宣言
class Actor;
class SceneBase;

/// <summary>
/// 戦闘を監視するクラス
/// </summary>
class FightObserver : public Behavior
{
public:
	// コンストラクタ
	FightObserver(Actor* owner, unsigned short players_num, unsigned short defeat_enemies, SceneBase* scene)
		: Behavior(owner), m_playersNum(players_num), m_alivePlayersNum(players_num), m_defeatEnemiesNum(defeat_enemies), p_scene(scene) {};

	// デストラクタ
	~FightObserver() {};

	// 通知を受け取る
	void OnNotify(EventList event) override;

private:
	// プレイヤー数
	unsigned short m_playersNum;

	// 生きているプレイヤー数
	unsigned short m_alivePlayersNum;

	// 倒すべき敵の数
	unsigned short m_defeatEnemiesNum;

	// 倒した敵の数
	unsigned short m_defeatedEnemiesNum = 0;

	// 現在シーン
	SceneBase* p_scene;
};

#endif