#pragma once

// 機体データ
struct BodyData
{
	short hp;			  // 体力
	float rotateSpeed;	  // 回転速度
	float accele;		  // 加速度
	short attackPower;	  // 通常攻撃力
};

// 翼のデータ
struct WingData
{
	short hp;			  // 体力
	float rotateSpeed;	  // 回転速度
	float accele;		  // 加速度
};

// ディフーザーのデータ
struct DiffuserData
{
	short hp;			  // 体力
	float rotateSpeed;	  // 回転速度
	float accele;		  // 加速度
};

// スペシャル武器のデータ
struct SpecialWeaponData
{
	short specialAttack;	  // スペシャル攻撃力
};

struct FighterData
{
	short id;
	BodyData body;
	WingData wing;
	DiffuserData diffuser;
	SpecialWeaponData specialWeapon;
};
