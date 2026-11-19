#pragma once

// 機体データ
struct BodyData
{
	short hp;			  // 体力
	float rotateSpeed;	  // 回転速度
	float accele;		  // 加速度
	float attackPower;	  // 通常攻撃力
	int handle;
};

// 翼のデータ
struct WingData
{
	short hp;			  // 体力
	float rotateSpeed;	  // 回転速度
	float accele;		  // 加速度
	int handle;
};

// ディフーザーのデータ
struct DiffuserData
{
	short hp;			  // 体力
	float rotateSpeed;	  // 回転速度
	float accele;		  // 加速度
	int handle;
};

// スペシャル武器のデータ
struct SpecialWeaponData
{
	short specialAttack;	  // スペシャル攻撃力
};

// 戦闘機の構成
struct FighterData
{
	short id;							  // ID
	BodyData body;						  // 機体
	WingData wing;						  // 翼
	DiffuserData diffuser;				  // ディフューザー
	SpecialWeaponData specialWeapon;	  // スペシャル武器
};

// 戦闘機ステータス
struct FighterStatus
{
	short hp;				  // 体力 
	float rotateSpeed;		  // 回転速度 
	float accele;			  // 加速度 
	short attackPower;		  // 通常攻撃力
	short specialAttack;	  // スペシャル攻撃力
};

// ステータス計算関数
FighterStatus CalculateFighterStatus(
	const BodyData& body,
	const WingData& wing,
	const DiffuserData& diffuser,
	const SpecialWeaponData& weapon);