#ifndef _ACTORLAYER_H
#define _ACTORLAYER_H

// アクターのレイヤー
// 当たり判定等に使用
enum class ActorLayer
{
	Default,

	Player,
	PlayerBullet,

	Enemy,
	EnemyBullet,

	Terrain,
};

#endif