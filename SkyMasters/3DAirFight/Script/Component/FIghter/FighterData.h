#pragma once

// 機体データ
struct BodyData
{
	int hp;				  // 体力
	float rotateSpeed;	  // 回転速度
	float accele;		  // 加速度
	int attackPower;	  // 通常攻撃力
};

// 翼のデータ
struct WingData
{
	int hp;				  // 体力
	float rotateSpeed;	  // 回転速度
	float accele;		  // 加速度
};

// ディフーザーのデータ
struct DiffuserData
{
	int hp;				  // 体力
	float rotateSpeed;	  // 回転速度
	float accele;		  // 加速度
};

// スペシャル武器のデータ
struct SpecialWeaponData
{
	int specialAttack;	  // スペシャル攻撃力
};

struct FighterData
{
	BodyData body;
	WingData wing;
	DiffuserData diffuser;
	SpecialWeaponData specialWeapon;
};
