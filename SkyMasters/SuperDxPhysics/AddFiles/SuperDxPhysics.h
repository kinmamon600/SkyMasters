#ifndef __SUPER_DX_PHYSICS_H__
#define __SUPER_DX_PHYSICS_H__

/*
* SuperDxPhysics
* Ver 1.1.2
*
* 注意:ここでの「物理オブジェクト」とは、描画されるものを指します。
*/

// ライブラリ・ヘッダ
#include "DxLib.h"				// https://dxlib.xsrv.jp/dxfunc.html

#include "../GamePhysicsSdk/extra/physics_effects/include/physics_effects.h"
#include "pfx_rigidbody_world.h"
#include "physics_func.h"

#include "VTXdata/box.h"
#include "VTXdata/sphere.h"
#include "VTXdata/cylinder.h"

namespace SDP {
	// 物理オブジェクトの最大個数(SuperDxPhysics使用時に限る)
	// 物理エンジン側の最大数もあるが、描画が原因でソフトウェアが落ちないようにここで設定
	const unsigned int PHYSICS_OBJECT_MAX = 512;

	// 凸メッシュオブジェクトの最大個数(SuperDxPhysics使用時に限る)
	// ConvexMeshが重くバグりやすいため設定
	const unsigned int CONVEX_MESH_MAX = 16;

	// IDのNULL設定
	const int ID_NULL = -1;

	// バッファハンドルのNULL設定
	const int BUFFERHANDLE_NULL = -1;

	// メッシュデータ格納用のクラス
	class MeshDatas
	{
	private:
		unsigned int vtxCnt;
		unsigned int idxCnt;
		float* vtxData;
		unsigned short* idxData;

	public:
		// コンストラクタ
		MeshDatas() : vtxCnt(0), idxCnt(0), vtxData(0), idxData(0) {}

		MeshDatas(unsigned int vtx_cnt, unsigned int idx_cnt, float* vtx_data, unsigned short* idx_data)
			: vtxCnt(vtx_cnt), idxCnt(idx_cnt), vtxData(vtx_data), idxData(idx_data) {
		}

		// デストラクタ
		~MeshDatas() noexcept {}

		// 関数
		unsigned int GetVtxCnt() { return vtxCnt; };
		unsigned int GetIdxCnt() { return idxCnt; };
		float* GetVtxData() { return vtxData; };
		unsigned short* GetIdxData() { return idxData; };
	};

	// 初期化関数
	bool PhysicsInit(const VECTOR& size);

	// 終了関数
	void PhysicsRelease();

	// 物理世界のリセット
	void ResetPhysicsWorld();

	// シミュレーション
	void SimulatePhysics();

	// 重力設定
	void SetGravity(float gravity);

	// 重力取得
	float GetGravity();

	// 物理オブジェクトの生成
	int CreatePhysicalSphere(const VECTOR& pos, float radius, ePfxMotionType type, float mass, const COLOR_U8& color);
	int CreatePhysicalBox(const VECTOR& pos, const VECTOR& size, ePfxMotionType type, float mass, const COLOR_U8& color);
	int CreatePhysicalCylinder(const VECTOR& pos, float h_length, float radius, ePfxMotionType type, float mass, const COLOR_U8& color);
	int CreatePhysicalCapsule(const VECTOR& pos, float h_length, float radius, ePfxMotionType type, float mass, const COLOR_U8& color);

	int CreatePhysicalLargeTriMesh(const VECTOR& pos, MeshDatas* datas, ePfxMotionType type, float mass, const COLOR_U8& color);
	int CreatePhysicalConvexMesh(const VECTOR& pos, MeshDatas* datas, ePfxMotionType type, float mass, const COLOR_U8& color);

	int CreatePhysicalGround(const COLOR_U8& color);

	// 物理オブジェクトの削除
	void DestroyPhysicalObject(unsigned int id);

	// 不動ジョイントの設定
	// 自動的に非接触オブジェクト化します
	unsigned int AddPhysicalJointFixed(unsigned int obj1_id, unsigned int obj2_id, const VECTOR& point);

	// ジョイントの削除
	void DestroyJoint(unsigned int joint_id);

	// メッシュデータのスケール設定
	void InitScale(unsigned int vtxCnt, float* vtxData, float scale);

	// 物理オブジェクトの描画
	void RenderPhysicalObject();

	// 物理オブジェクトの表示・非表示設定
	void SetRenderFlag(unsigned int id, bool flag);

	// 物理オブジェクトの表示・非表示取得
	bool GetRenderFlag(unsigned int id);

	// 総オブジェクト数の取得
	unsigned int GetTotalObjectNumber();

	// 物理オブジェクトの座標設定
	void SetPosition(unsigned int id, const VECTOR& pos);

	// 物理オブジェクトの座標取得
	VECTOR GetPosition(unsigned int id);

	// 物理オブジェクトの回転設定
	void SetRotate(unsigned int id, const VECTOR& rotate);

	// 物理オブジェクトの回転取得
	VECTOR GetRotate(unsigned int id);

	// 物理オブジェクトの向き取得
	VECTOR GetDirection(unsigned int id, const VECTOR& std_vec);

	// 物理オブジェクトの色・アンビエントカラー設定
	void SetColor(unsigned int id, const COLOR_U8& color);
	void SetAmbient(unsigned int id, const COLOR_F& amb);

	// 物理オブジェクトの速度設定
	void SetLinerVelocity(unsigned int id, const VECTOR& vec);
	void SetAngularVelocity(unsigned int id, const VECTOR& vec);

	// 物理オブジェクトの速度取得
	VECTOR GetLinerVelocity(unsigned int id);
	VECTOR GetAngularVelocity(unsigned int id);

	// 物理オブジェクトの質量・逆質量設定
	void SetMass(unsigned int id, float mass);
	void SetMassInv(unsigned int id, float inv_mass);

	// 物理オブジェクトの質量・逆質量取得
	float GetMass(unsigned int id);
	float GetMassInv(unsigned int id);

	// 物理オブジェクトの摩擦設定
	void SetFriction(unsigned int id, float fric);

	// 物理オブジェクトの摩擦取得
	float GetFriction(unsigned int id);

	// 物理オブジェクトの反発係数設定
	void SetRestitution(unsigned int id, float elastic);

	// 物理オブジェクトの反発係数取得
	float GetRestitution(unsigned int id);

	// 物理オブジェクトの接触判定
	bool IsContact(unsigned int id_a, unsigned int id_b);

	// 物理オブジェクトの非接触設定
	void SetNonContactPair(unsigned int obj1_id, unsigned int obj2_id);

	// 物理オブジェクトの非接触解除
	void ReleaseNonContactPair(unsigned int obj1_id, unsigned int obj2_id);

	// レイを放つ
	// directionは長さも持つ
	int RayCast(const VECTOR& start, const VECTOR& direction);

	// レイを描画する
	// 第三引数に上記の RayCast() を設定するとよい
	void DrawRay(const VECTOR& start, const VECTOR& direction, int object_id);
}

#endif