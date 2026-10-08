#ifndef _TERRAIN_H
#define _TERRAIN_H

// ライブラリ・ヘッダ
#include <string>
#include <cmath>

#include "DxLib.h"  // https://dxlib.xsrv.jp/dxfunc.html
#include "SuperDxPhysics.h"

#include "Settings.h"
#include "Sky.h"

// メッシュデータ
#include "../MeshDatas/TerrainBase_Mesh.h"
#include "../MeshDatas/TerrainBridge_Mesh.h"
#include "../MeshDatas/TerrainTower_Mesh.h"
#include "../MeshDatas/TerrainBuilding_Mesh.h"

// 定数
// 地形を構成する物理オブジェクト数
const unsigned short TERRAIN_OBJECT_NUM = 7;

// 地形オブジェクトのオフセット
const VECTOR TERRAIN_OFFSET = VGet(0.0f, -10.0f, 0.0f);

// 背景表示時のカメラ角度・回転半径・回転角速度
const float TERRAIN_BACKGROUND_CAMANGLE = 10.0f;
const float TERRAIN_BACKGROUND_RADIUS = 2000.0f;
const float TERRAIN_BACKGROUND_ANGULARVELOCITY = 20.0f;

// 背景表示時の描画範囲
const float TERRAIN_BACKGROUND_CAMNEAR = 300.0f;
const float TERRAIN_BACKGROUND_CAMFAR = 5000.0f;

// 地形接触時のダメージ
const unsigned short TERRAIN_DAMAGE = 50;

class Terrain
{
public:
	// コンストラクタ
	Terrain();

	// デストラクタ
	~Terrain();

	// 地形の生成
	void CreateTerrain();

	// 地形オブジェクトのID取得
	int GetID(unsigned short num) const;

	// 地形を背景として回転表示
	void DisplayAsBackground();

private:
	// 地形を構成するメッシュデータ
	SDP::MeshDatas* meshDatas[TERRAIN_OBJECT_NUM]{};

	// 地形を構成する色
	COLOR_U8 colors[TERRAIN_OBJECT_NUM]{};

	// 地形オブジェクトのID
	int ids[TERRAIN_OBJECT_NUM]{};

	// 背景表示用のタイマー(sec)
	double backgroundTimer = 0.0;
};

#endif