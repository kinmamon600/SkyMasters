#ifndef _FIGHTER_H
#define _FIGHTER_H

// ライブラリ・ヘッダ
#include <string>
#include <vector>

#include "DxLib.h"  // https://dxlib.xsrv.jp/dxfunc.html
#include "SuperDxPhysics.h"
#include "Beam.h"

// メッシュデータ
#include "../MeshDatas/Meshes_Fighter01.h"
#include "../MeshDatas/Mesh_beam.h"

// 名前空間
using namespace sce::PhysicsEffects;

// 定数

// ファイターの総数
const unsigned short TOTAL_FIGHTER_NUM = 1;

// ファイターのスケール
const float FIGHTER_SCALE = 0.01f;

// 一機あたりのパーツ数
const unsigned short FIGHTER_PARTS_NUM = 5;

// 一機あたりのジョイント数
const unsigned short FIGHTER_JOINT_NUM = 10;

// ファイターの反射係数・摩擦係数
const float FIGHTER_RESTITUTION = 0.9f;
const float FIGHTER_FRICTION = 0.5f;

// ファイター1機あたりの弾数制限
const unsigned short FIGHTER_BEAM_MAX = 60;

// 全機体のスケールの初期化
void InitFightersScale();

/// <summary>
/// 各ファイターのメッシュやパラメータのクラス
/// </summary>
class FighterParams
{
public:
	// コンストラクタ
	FighterParams() {}

	// デストラクタ
	~FighterParams() {};

	// パラメータのセット

	// 機体名のセット
	void SetName(std::string _name);

	// メッシュデータのセット
	void SetMeshes(unsigned short num, SDP::MeshDatas& mesh);

	// 速度パラメータのセット
	void SetSpeedParams(float default_spd, float boost_spd, float brake_spd, float accel, float decel);

	// 角速度パラメータのセット
	void SetAngularVelocitys(float pitch, float roll, float yaw);

	// 機体重量のセット
	void SetMass(float _mass);

	// 銃口座標の追加
	void AddMuzzlePosition(const VECTOR& pos);


	// パラメータの取得

	// 機体名の取得
	std::string GetName();

	// メッシュデータの取得(ポインタ)
	SDP::MeshDatas* GetMeshes(unsigned short num);

	// 各種パラメータの取得
	float GetDefaultSpeed() const;
	float GetBoostSpeed() const;
	float GetBrakeSpeed() const;
	float GetAcceleration() const;
	float GetDeceleration() const;
	float GetPitchAngularVelocity() const;
	float GetRollAngularVelocity() const;
	float GetYawAngularVelocity() const;
	float GetMass() const;

	// 銃口数の取得
	unsigned short GetMuzzleNum();

	// 銃口座標の取得
	VECTOR GetMuzzlePosition(unsigned short num);

private:
	// 機体名
	std::string name{};

	// メッシュデータ
	SDP::MeshDatas meshes[FIGHTER_PARTS_NUM]{};

	// 数値パラメータ
	float defaultSpeed = 0.0f;			// 通常飛行速度(目標値)
	float boostSpeed = 0.0f;			// ブースト時の飛行速度(目標値)
	float brakeSpeed = 0.0f;			// ブレーキ時の飛行速度(目標値)
	float acceleration = 0.0f;			// 加速度
	float deceleration = 0.0f;			// 減速度

	float pitchAngularVelocity = 0.0f;	// ピッチ(縦揺れ)角速度
	float rollAngularVelocity = 0.0f;	// ロール(横揺れ)角速度
	float yawAngularVelocity = 0.0f;	// ヨー　(偏揺れ)角速度

	float mass = 0.0f;					// 機体重量

	// 座標パラメータ
	std::vector<VECTOR> muzzlePositions{};
};

/// <summary>
/// 全機体のデータを管理するクラス
/// ハンガー(格納庫)
/// </summary>
class Hangar
{
public:
	// コンストラクタ
	Hangar();

	// デストラクタ
	~Hangar() {};

	// 機体データの取得
	FighterParams* GetFighter(unsigned short num);

	// ビームのメッシュデータ取得
	SDP::MeshDatas* GetBeamMeshData();

private:
	// 機体データ
	FighterParams fighters[TOTAL_FIGHTER_NUM];

	// ビームのメッシュデータ
	SDP::MeshDatas beamMeshData;

	// 機体データの初期化関数
	void InitFighterData();
};

/// <summary>
/// 当たり判定用のID
/// </summary>
class FighterPartsID
{
public:
	// コンストラクタ
	FighterPartsID() : ids() {};

	// デストラクタ
	~FighterPartsID() {};

	// IDの設定
	void SetPartsID(unsigned short num, unsigned int id);

	// IDの取得
	int GetPartsID(unsigned short num = 0) const;

private:
	int ids[FIGHTER_PARTS_NUM];
};

#endif