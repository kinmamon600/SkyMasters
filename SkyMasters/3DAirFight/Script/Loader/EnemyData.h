#pragma once
#include"DxLib.h"

struct EnemyStatus
{
	short id;
	float hp;
	short attack;
};

struct EnemyTransform
{
	short enemyID;		 // “G‚Ìí—Ş‚Ì”»•Ê—p
	short instanceID;		 // “¯‚¶í—Ş‚Ì“G‚ğ”»’f‚·‚é—p
	VECTOR position;	 // À•W
	VECTOR rotation;	 // ‰ñ“]
	VECTOR scale;		 // ‘å‚«‚³
};

