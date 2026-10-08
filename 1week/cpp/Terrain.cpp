// ライブラリ・ヘッダ
#include "Terrain.h"

// クラス「Terrain」の関数等

Terrain::Terrain()
{
	// 地形データのセット
	meshDatas[0] = new SDP::MeshDatas(NUM_BASE_VTX, NUM_BASE_IDX, base_vtx, base_idx);
	colors[0] = GetColorU8(100, 100, 100, 0);

	meshDatas[1] = new SDP::MeshDatas(NUM_BRIDGE_VTX, NUM_BRIDGE_IDX, bridge_vtx, bridge_idx);
	colors[1] = GetColorU8(110, 240, 110, 0);

	meshDatas[2] = new SDP::MeshDatas(NUM_TOWER_VTX, NUM_TOWER_IDX, tower_vtx, tower_idx);
	colors[2] = GetColorU8(240, 255, 255, 0);

	meshDatas[3] = new SDP::MeshDatas(NUM_BUILDING_A_VTX, NUM_BUILDING_A_IDX, building_a_vtx, building_a_idx);
	colors[3] = GetColorU8(240, 255, 255, 0);

	meshDatas[4] = new SDP::MeshDatas(NUM_BUILDING_B_VTX, NUM_BUILDING_B_IDX, building_b_vtx, building_b_idx);
	colors[4] = GetColorU8(240, 255, 255, 0);

	meshDatas[5] = new SDP::MeshDatas(NUM_BUILDING_C_VTX, NUM_BUILDING_C_IDX, building_c_vtx, building_c_idx);
	colors[5] = GetColorU8(240, 255, 255, 0);

	meshDatas[6] = new SDP::MeshDatas(NUM_BUILDING_D_VTX, NUM_BUILDING_D_IDX, building_d_vtx, building_d_idx);
	colors[6] = GetColorU8(240, 255, 255, 0);
}

Terrain::~Terrain()
{
	for (int i = 0; i < TERRAIN_OBJECT_NUM; ++i)
	{
		delete meshDatas[i];
		meshDatas[i] = nullptr;
	}
}

void Terrain::CreateTerrain()
{
	for (int i = 0; i < TERRAIN_OBJECT_NUM; ++i)
	{
		// 地形生成
		// 逆質量0 = 無限の質量に設定
		ids[i] = SDP::CreatePhysicalLargeTriMesh(TERRAIN_OFFSET, meshDatas[i], kPfxMotionTypeFixed, 0, colors[i]);
		SDP::SetMassInv(ids[i], 0);
	}

#if 1
	SDP::SetNonContactPair(ids[0], ids[1]);
	SDP::SetNonContactPair(ids[0], ids[2]);
	SDP::SetNonContactPair(ids[0], ids[3]);
	SDP::SetNonContactPair(ids[0], ids[4]);
	SDP::SetNonContactPair(ids[0], ids[5]);
	SDP::SetNonContactPair(ids[0], ids[6]);

	SDP::SetNonContactPair(ids[1], ids[2]);
	SDP::SetNonContactPair(ids[1], ids[3]);
	SDP::SetNonContactPair(ids[1], ids[4]);
	SDP::SetNonContactPair(ids[1], ids[5]);
	SDP::SetNonContactPair(ids[1], ids[6]);

	SDP::SetNonContactPair(ids[2], ids[3]);
	SDP::SetNonContactPair(ids[2], ids[4]);
	SDP::SetNonContactPair(ids[2], ids[5]);
	SDP::SetNonContactPair(ids[2], ids[6]);

	SDP::SetNonContactPair(ids[3], ids[4]);
	SDP::SetNonContactPair(ids[3], ids[5]);
	SDP::SetNonContactPair(ids[3], ids[6]);

	SDP::SetNonContactPair(ids[4], ids[5]);
	SDP::SetNonContactPair(ids[4], ids[6]);

	SDP::SetNonContactPair(ids[5], ids[6]);
#endif
}

int Terrain::GetID(unsigned short num) const
{
	return ids[num];
}

void Terrain::DisplayAsBackground()
{
	float rad = TERRAIN_BACKGROUND_CAMANGLE * DX_PI_F / 180.0f;

	float base = TERRAIN_BACKGROUND_RADIUS * cosf(rad);
	float height = TERRAIN_BACKGROUND_RADIUS * sinf(rad);

	// ロドリゲスの回転公式でカメラ座標を回転
	float angle = backgroundTimer * TERRAIN_BACKGROUND_ANGULARVELOCITY;
	rad = angle * DX_PI_F / 180.0f;
	float c = std::cos(rad);
	float s = std::sin(rad);
	VECTOR direction = VGet(0.0f, 0.0f, -1.0f);
	VECTOR camera_pos = VAdd(VScale(direction, c), VScale(VCross(VGet(0.0f, 1.0f, 0.0f), direction), s));
	camera_pos = VScale(camera_pos, base);
	camera_pos.y = height;

	// 空の描画
	DrawBox(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, GetSkyColor(height), TRUE);

	// カメラ位置を設定し、地形を描画
	SetCameraPositionAndTarget_UpVecY(camera_pos, TERRAIN_OFFSET);

	for (int i = 0; i < TERRAIN_OBJECT_NUM; ++i)
	{
		SDP::RenderSDPMesh(TERRAIN_OFFSET, meshDatas[i], colors[i]);
	}

	backgroundTimer = (double)GetNowCount() / 1000.0;
}
