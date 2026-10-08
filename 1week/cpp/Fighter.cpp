// ライブラリ・ヘッダ
#include "Fighter.h"

void InitFightersScale()
{
	SDP::InitScale(Fighter01::NUM_CANOPY_VTX, Fighter01::canopy_vtx, FIGHTER_SCALE);
	SDP::InitScale(Fighter01::NUM_BODY01_VTX, Fighter01::body01_vtx, FIGHTER_SCALE);
	SDP::InitScale(Fighter01::NUM_BODY02_VTX, Fighter01::body02_vtx, FIGHTER_SCALE);
	SDP::InitScale(Fighter01::NUM_BODY03_VTX, Fighter01::body03_vtx, FIGHTER_SCALE);
	SDP::InitScale(Fighter01::NUM_WING_VTX, Fighter01::wing_vtx, FIGHTER_SCALE);

	SDP::InitScale(NUM_BEAM_VTX, beam_vtx, BEAM_SCALE);
}

// クラス「FighterParams」の関数等

void FighterParams::SetName(std::string _name)
{
	name = _name;
}

void FighterParams::SetMeshes(unsigned short num, SDP::MeshDatas& mesh)
{
	if (num >= FIGHTER_PARTS_NUM) { return; }
	meshes[num] = mesh;
}

void FighterParams::SetSpeedParams(float default_spd, float boost_spd, float brake_spd, float accel, float decel)
{
	defaultSpeed = default_spd;
	boostSpeed = boost_spd;
	brakeSpeed = brake_spd;
	acceleration = accel;
	deceleration = decel;
}

void FighterParams::SetAngularVelocitys(float pitch, float roll, float yaw)
{
	pitchAngularVelocity = pitch;
	rollAngularVelocity = roll;
	yawAngularVelocity = yaw;
}

void FighterParams::SetMass(float _mass)
{
	mass = _mass;
}

void FighterParams::AddMuzzlePosition(const VECTOR& pos)
{
	muzzlePositions.push_back(pos);
}

std::string FighterParams::GetName() { return name; }

SDP::MeshDatas* FighterParams::GetMeshes(unsigned short num)
{
	if (num >= FIGHTER_PARTS_NUM) { return nullptr; }
	return &(meshes[num]);
}

float FighterParams::GetDefaultSpeed() const { return defaultSpeed; }
float FighterParams::GetBoostSpeed() const { return boostSpeed; }
float FighterParams::GetBrakeSpeed() const { return brakeSpeed; }
float FighterParams::GetAcceleration() const { return acceleration; }
float FighterParams::GetDeceleration() const { return deceleration; }
float FighterParams::GetPitchAngularVelocity() const { return pitchAngularVelocity; }
float FighterParams::GetRollAngularVelocity() const { return rollAngularVelocity; }
float FighterParams::GetYawAngularVelocity() const { return yawAngularVelocity; }
float FighterParams::GetMass() const { return mass; }

unsigned short FighterParams::GetMuzzleNum() { return muzzlePositions.size(); }

VECTOR FighterParams::GetMuzzlePosition(unsigned short num) { return muzzlePositions[num]; }

// 以下クラス「Hangar」の関数等

Hangar::Hangar()
{
	// 機体データの設定
	InitFighterData();

	// ビームのメッシュデータ設定
	beamMeshData = SDP::MeshDatas(NUM_BEAM_VTX, NUM_BEAM_IDX, beam_vtx, beam_idx);
}

void Hangar::InitFighterData()
{
	// No.1
	SDP::MeshDatas fighter01_meshes[FIGHTER_PARTS_NUM];
	fighter01_meshes[0] = { Fighter01::NUM_CANOPY_VTX, Fighter01::NUM_CANOPY_IDX, Fighter01::canopy_vtx, Fighter01::canopy_idx };
	fighter01_meshes[1] = { Fighter01::NUM_BODY01_VTX, Fighter01::NUM_BODY01_IDX, Fighter01::body01_vtx, Fighter01::body01_idx };
	fighter01_meshes[2] = { Fighter01::NUM_BODY02_VTX, Fighter01::NUM_BODY02_IDX, Fighter01::body02_vtx, Fighter01::body02_idx };
	fighter01_meshes[3] = { Fighter01::NUM_BODY03_VTX, Fighter01::NUM_BODY03_IDX, Fighter01::body03_vtx, Fighter01::body03_idx };
	fighter01_meshes[4] = { Fighter01::NUM_WING_VTX, Fighter01::NUM_WING_IDX, Fighter01::wing_vtx, Fighter01::wing_idx };

	fighters[0].SetName("1号");
	fighters[0].SetSpeedParams(300.0f, 360.0f, 240.0f, 1000.0f, -1000.0f);
	fighters[0].SetAngularVelocitys(1.2f, 1.4f, 1.0f);
	fighters[0].SetMass(12.0f);
	fighters[0].AddMuzzlePosition(VGet(5.0f, 0.0f, -1.0f));
	fighters[0].AddMuzzlePosition(VGet(-5.0f, 0.0f, -1.0f));

	// 全機まとめてメッシュデータのセット
	for (int i = 0; i < FIGHTER_PARTS_NUM; ++i)
	{
		fighters[0].SetMeshes(i, fighter01_meshes[i]);
	}
}

FighterParams* Hangar::GetFighter(unsigned short num)
{
	if (num >= TOTAL_FIGHTER_NUM) return &fighters[0];
	return &fighters[num];
}

SDP::MeshDatas* Hangar::GetBeamMeshData()
{
	return &beamMeshData;
}

// 以下クラス「FighterPartsID」の関数等

void FighterPartsID::SetPartsID(unsigned short num, unsigned int id)
{
	if (num >= FIGHTER_PARTS_NUM) { return; }
	ids[num] = id;
}

int FighterPartsID::GetPartsID(unsigned short num) const
{
	if (num >= FIGHTER_PARTS_NUM) { return -1; }
	return ids[num];
}
