// ライブラリ・ヘッダ
#include <vector>

#include "SuperDxPhysics.h"

using namespace std;
using namespace SDP;

// 総オブジェクト数
unsigned int g_totalObjectNumber = 0;

// 各オブジェクトの色とマテリアル
COLOR_U8 g_physicsObjectColor[PHYSICS_OBJECT_MAX];
MATERIALPARAM g_physicsObjectMaterial[PHYSICS_OBJECT_MAX];

const COLOR_F COLORF_ZERO = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
const float AMBIENT_MULTIPLIER = 0.2f;
const float MATERIAL_POWER = 20.0f;

// 各オブジェクトの表示・非表示設定
bool g_renderFlags[PHYSICS_OBJECT_MAX];

// メッシュデータとID管理用のクラス
#if 0
class RenderMesh
{
private:
	unsigned int objectId;
	MeshDatas* meshDatas;

public:
	RenderMesh(unsigned int obj_id, MeshDatas* datas)
		: objectId(obj_id), meshDatas(datas){ }

	unsigned int GetId() { return objectId; }
	MeshDatas* GetMashDatas() { return meshDatas; }
};
#endif

// メッシュデータのリスト
//static vector<RenderMesh> renderMeshes;
static vector<MeshDatas*> g_renderMeshes{};
static vector<unsigned int> g_renderMeshesID{};

// 凸メッシュデータ
// データを保持し続けるためグローバル
PfxConvexMesh g_convexMeshes[CONVEX_MESH_MAX];
short g_convexMeshesID[CONVEX_MESH_MAX];

// 初期化関数
bool SDP::PhysicsInit(const VECTOR& size)
{
	for (int i = 0; i < PHYSICS_OBJECT_MAX; ++i)
	{
		g_physicsObjectColor[i] = COLOR_U8();
		g_physicsObjectMaterial[i] = MATERIALPARAM();
	}

	g_renderMeshes.clear();
	g_renderMeshesID.clear();

	for (int i = 0; i < CONVEX_MESH_MAX; ++i)
	{
		g_convexMeshes[i] = PfxConvexMesh();
		g_convexMeshesID[i] = ID_NULL;
	}

	return physicsInit(PfxVector3(size.x, size.y, size.z));
}

// 終了関数
void SDP::PhysicsRelease()
{
	physicsRelease();
}

// 物理世界のリセット
void SDP::ResetPhysicsWorld()
{
	physicsResetWorld();

	for (int i = 0; i < PHYSICS_OBJECT_MAX; ++i)
	{
		g_physicsObjectColor[i] = COLOR_U8();
		g_physicsObjectMaterial[i] = MATERIALPARAM();
	}

	g_renderMeshes.clear();
	g_renderMeshesID.clear();

	for (int i = 0; i < CONVEX_MESH_MAX; ++i)
	{
		g_convexMeshes[i] = PfxConvexMesh();
		g_convexMeshesID[i] = ID_NULL;
	}
}

// シミュレーション
void SDP::PhysicsSimulate()
{
	physicsSimulate();
}

// 重力設定
void SDP::SetGravity(float gravity)
{
	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	rb_world->setGravity(PfxVector3(0.0f, gravity, 0.0f));
}

// 重力取得
float SDP::GetGravity()
{
	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	PfxVector3 gravity_vec = rb_world->getGravity();
	return gravity_vec.getY();
}

// 物理オブジェクト:球の生成
int SDP::CreatePhysicalSphere
	(const VECTOR& pos, float radius, ePfxMotionType type, float mass, const COLOR_U8& color)
{
	if (g_totalObjectNumber >= PHYSICS_OBJECT_MAX) { return ID_NULL; }
	++g_totalObjectNumber;

	PfxRigidState state;
	PfxRigidBody body;
	PfxCollidable collidable;

	PfxSphere sphere(radius);
	PfxShape shape;
	shape.reset();
	shape.setSphere(sphere);
	collidable.reset();
	collidable.addShape(shape);
	collidable.finish();
	body.reset();
	body.setMass(mass);
	body.setInertia(pfxCalcInertiaSphere(radius, mass));
	state.reset();
	state.setPosition(PfxVector3(pos.x, pos.y, -pos.z));
	state.setMotionType(type);
	state.setUseSleep(1);

	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	int id = rb_world->addRigidBody(state, body, collidable);
	SetColor(id, color);
	g_renderFlags[id] = true;
	return id;
}

// 物理オブジェクト:箱の生成
int SDP::CreatePhysicalBox
	(const VECTOR& pos, const VECTOR& size, ePfxMotionType type, float mass, const COLOR_U8& color)
{
	if (g_totalObjectNumber >= PHYSICS_OBJECT_MAX) { return ID_NULL; }
	++g_totalObjectNumber;

	PfxRigidState state;
	PfxRigidBody body;
	PfxCollidable collidable;

	PfxBox box(size.x, size.y, size.z);
	PfxShape shape;
	shape.reset();
	shape.setBox(box);
	collidable.reset();
	collidable.addShape(shape);
	collidable.finish();
	body.reset();
	body.setMass(mass);
	body.setInertia(pfxCalcInertiaBox(PfxVector3(pos.x, pos.y, -pos.z), mass));
	state.reset();
	state.setPosition(PfxVector3(pos.x, pos.y, -pos.z));
	state.setMotionType(type);
	state.setUseSleep(1);

	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	int id = rb_world->addRigidBody(state, body, collidable);
	SetColor(id, color);
	g_renderFlags[id] = true;
	return id;
}

// 物理オブジェクト:筒の生成
int SDP::CreatePhysicalCylinder
	(const VECTOR& pos, float h_length, float radius, ePfxMotionType type, float mass, const COLOR_U8& color)
{
	if (g_totalObjectNumber >= PHYSICS_OBJECT_MAX) { return ID_NULL; }
	++g_totalObjectNumber;

	PfxRigidState state;
	PfxRigidBody body;
	PfxCollidable collidable;

	PfxCylinder cylinder(h_length, radius);
	PfxShape shape;
	shape.reset();
	shape.setCylinder(cylinder);
	collidable.reset();
	collidable.addShape(shape);
	collidable.finish();
	body.reset();
	body.setMass(mass);
	body.setInertia(pfxCalcInertiaCylinderX(h_length, radius, mass));
	state.reset();
	state.setPosition(PfxVector3(pos.x, pos.y, -pos.z));
	state.setMotionType(type);
	state.setUseSleep(1);

	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	int id = rb_world->addRigidBody(state, body, collidable);
	SetColor(id, color);
	g_renderFlags[id] = true;
	return id;
}

// 物理オブジェクト:カプセルの生成
int SDP::CreatePhysicalCapsule
	(const VECTOR& pos, float h_length, float radius, ePfxMotionType type, float mass, const COLOR_U8& color)
{
	if (g_totalObjectNumber >= PHYSICS_OBJECT_MAX) { return ID_NULL; }
	++g_totalObjectNumber;

	PfxRigidState state;
	PfxRigidBody body;
	PfxCollidable collidable;

	PfxCapsule capsule(h_length, radius);
	PfxShape shape;
	shape.reset();
	shape.setCapsule(capsule);
	collidable.reset();
	collidable.addShape(shape);
	collidable.finish();
	body.reset();
	body.setMass(mass);
	body.setInertia(pfxCalcInertiaCylinderX(h_length + radius, radius, mass));
	state.reset();
	state.setPosition(PfxVector3(pos.x, pos.y, -pos.z));
	state.setMotionType(type);
	state.setUseSleep(1);

	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	int id = rb_world->addRigidBody(state, body, collidable);
	SetColor(id, color);
	g_renderFlags[id] = true;
	return id;
}

// 物理オブジェクト:コンベックスメッシュオブジェクトの生成
int SDP::CreatePhysicalConvexMesh(const VECTOR& pos, MeshDatas* datas, ePfxMotionType type, float mass, const COLOR_U8& color)
{
	if (g_totalObjectNumber >= PHYSICS_OBJECT_MAX) { return ID_NULL; }
	++g_totalObjectNumber;

	short cm_id = ID_NULL;
	for (int i = 0; i < CONVEX_MESH_MAX; ++i)
	{
		if (g_convexMeshesID[i] == ID_NULL)
		{
			cm_id = i;
			break;
		}
	}

	if(cm_id == ID_NULL) { return ID_NULL; }

	PfxCreateConvexMeshParam param;

	param.verts = datas->GetVtxData();
	param.numVerts = datas->GetVtxCnt();
	param.vertexStrideBytes = sizeof(float) * 6;

	param.triangles = datas->GetIdxData();
	param.numTriangles = datas->GetIdxCnt() / 3;
	param.triangleStrideBytes = sizeof(unsigned short) * 3;

	if (g_convexMeshes[cm_id].m_numVerts > 0) {
		pfxReleaseConvexMesh(g_convexMeshes[cm_id]);
	}

	PfxInt32 ret = pfxCreateConvexMesh(g_convexMeshes[cm_id], param);
	if (ret != SCE_PFX_OK) {
		SCE_PFX_PRINTF("Can't create gConvex mesh.\n");
	}

	// 慣性テンソルの算出
	// GamePhysicsSDKに球、ボックス、筒しかないためここで計算
	// 中心から全頂点への距離の平均を半径とする球で近似

#if 0
	VECTOR center_pos_vec{};
	float radius = 0.0f;
	for (int i = 0; i < param.numVerts; ++i)
	{
		center_pos_vec = VGet(param.verts[i * 6], param.verts[i * 6 + 1], param.verts[i * 6 + 2]);
		radius += (VSize(center_pos_vec) - radius) / (float)(i + 1);
	}
#endif

#if 1
	float center_x = 0.0f;
	float center_y = 0.0f;
	float center_z = 0.0f;
	for (int i = 0; i < param.numVerts; ++i)
	{
		center_x += (param.verts[i * 6] - center_x) / (float)(i + 1);
		center_y += (param.verts[i * 6 + 1] - center_y) / (float)(i + 1);
		center_z += (param.verts[i * 6 + 2] - center_z) / (float)(i + 1);
	}

	VECTOR center_pos_vec{};
	float radius = 0.0f;
	for (int i = 0; i < param.numVerts; ++i)
	{
		center_pos_vec = VGet(center_x - param.verts[i * 6], center_y - param.verts[i * 6 + 1], center_z - param.verts[i * 6 + 2]);
		radius += (VSize(center_pos_vec) - radius) / (float)(i + 1);
	}
#endif

	if (radius < 0.01f)
	{
		radius = 0.01f;
	}

	PfxRigidState state;
	PfxRigidBody body;
	PfxCollidable collidable;

	PfxShape shape;
	shape.reset();
	shape.setConvexMesh(&g_convexMeshes[cm_id]);
	collidable.reset();
	collidable.addShape(shape);
	collidable.finish();
	body.reset();
	body.setMass(mass);
	body.setInertia(pfxCalcInertiaSphere(radius, mass));
	state.reset();
	state.setPosition(PfxVector3(pos.x, pos.y, -pos.z));
	state.setMotionType(type);
	state.setUseSleep(1);

	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	int id = rb_world->addRigidBody(state, body, collidable);
	SetColor(id, color);
	g_renderFlags[id] = true;

	// メッシュデータ・メッシュIDの保存
	
	//RenderMesh render_mesh(id, &datas);
	//renderMeshs.push_back(render_mesh);
	g_renderMeshes.push_back(datas);
	g_renderMeshesID.push_back(id);

	// 凸メッシュIDの保存
	g_convexMeshesID[cm_id] = id;

	return id;
}

// 物理オブジェクト:ラージトライメッシュオブジェクトの生成
int SDP::CreatePhysicalLargeTriMesh
	(const VECTOR& pos, MeshDatas* datas, ePfxMotionType type, float mass, const COLOR_U8& color)
{
	if (g_totalObjectNumber >= PHYSICS_OBJECT_MAX) { return ID_NULL; }
	++g_totalObjectNumber;


	// GamePhysicsSDKの仕様通りメッシュの設定

	PfxLargeTriMesh* pLargeMesh = (PfxLargeTriMesh*)SCE_PFX_UTIL_ALLOC(16, sizeof(PfxLargeTriMesh));
	//SCE_PFX_ALWAYS_ASSERT(pLargeMesh);
	memset(pLargeMesh, 0, sizeof(PfxLargeTriMesh));
	
	PfxCreateLargeTriMeshParam param;

	param.verts = datas->GetVtxData();
	param.numVerts = datas->GetVtxCnt();
	param.vertexStrideBytes = sizeof(float) * 6;

	param.triangles = datas->GetIdxData();
	param.numTriangles = datas->GetIdxCnt() / 3;
	param.triangleStrideBytes = sizeof(unsigned short) * 3;

	// Use quantized value for vertices and facets
	param.flag |= SCE_PFX_MESH_FLAG_USE_QUANTIZED;

	// Use bvh structure
	param.flag |= SCE_PFX_MESH_FLAG_USE_BVH;

	// Print large mesh info
	param.flag |= SCE_PFX_MESH_FLAG_OUTPUT_INFO;

	// Apply user data
	param.userData = (PfxUInt32*)SCE_PFX_UTIL_ALLOC(16, sizeof(PfxUInt32) * datas->GetIdxCnt() / 3);
	for (int i = 0;i < datas->GetIdxCnt() / 3;i++) {
		param.userData[i] = i;
	}

	PfxInt32 ret = pfxCreateLargeTriMesh(*pLargeMesh, param);
	if (ret != SCE_PFX_OK) {
		SCE_PFX_PRINTF("Can't create large mesh. err = 0x%x\n", ret);
		//SCE_PFX_ALWAYS_ASSERT(ret == SCE_PFX_OK);
	}

	SCE_PFX_UTIL_FREE(param.userData);


	// 慣性テンソルの算出
	// GamePhysicsSDKに球、ボックス、筒しかないためここで計算
	// 中心から全頂点への距離の平均を半径とする球で近似
	
#if 1
	VECTOR center_pos_vec{};
	float radius = 0.0f;
	for (int i = 0; i < param.numVerts; ++i)
	{
		center_pos_vec = VGet(param.verts[i * 6], param.verts[i * 6 + 1], param.verts[i * 6 + 2]);
		radius += (VSize(center_pos_vec) - radius) / (float)(i + 1);
	}
#endif

#if 0
	float center_x = 0.0f;
	float center_y = 0.0f;
	float center_z = 0.0f;
	for (int i = 0; i < param.numVerts; ++i)
	{
		center_x += (param.verts[i * 6] - center_x) / (float)(i + 1);
		center_y += (param.verts[i * 6 + 1] - center_y) / (float)(i + 1);
		center_z += (param.verts[i * 6 + 2] - center_z) / (float)(i + 1);
	}

	VECTOR center_pos_vec{};
	float radius = 0.0f;
	for (int i = 0; i < param.numVerts; ++i)
	{
		center_pos_vec = VGet(center_x - param.verts[i * 6], center_y - param.verts[i * 6 + 1], center_z - param.verts[i * 6 + 2]);
		radius += (VSize(center_pos_vec) - radius) / (float)(i + 1);
	}
#endif

	if (radius < 0.01f)
	{
		radius = 0.01f;
	}


	// GamePhysicsSDKの仕様通りオブジェクトの設定

	PfxRigidState state;
	PfxRigidBody body;
	PfxCollidable collidable;

	PfxShape shape;
	shape.reset();
	shape.setLargeTriMesh(pLargeMesh);
	collidable.reset();
	collidable.addShape(shape);
	collidable.finish();
	body.reset();
	body.setMass(mass);
	body.setInertia(pfxCalcInertiaSphere(radius, mass));
	state.reset();
	state.setPosition(PfxVector3(pos.x, pos.y, -pos.z));
	state.setMotionType(type);
	state.setUseSleep(1);

	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	int id = rb_world->addRigidBody(state, body, collidable);
	SetColor(id, color);
	g_renderFlags[id] = true;

	// メッシュデータ・メッシュIDの保存

	//RenderMesh render_mesh(id, &datas);
	//renderMeshs.push_back(render_mesh);
	g_renderMeshes.push_back(datas);
	g_renderMeshesID.push_back(id);

	return id;
}

// 物理オブジェクト:床の生成
int SDP::CreatePhysicalGround(const COLOR_U8& color)
{
	if (g_totalObjectNumber >= PHYSICS_OBJECT_MAX) { return ID_NULL; }
	++g_totalObjectNumber;

	PfxRigidState state;
	PfxRigidBody body;
	PfxCollidable collidable;

	PfxBox box(150.0f, 2.5f, 150.0f);
	PfxShape shape;
	shape.reset();
	shape.setBox(box);
	collidable.reset();
	collidable.addShape(shape);
	collidable.finish();
	body.reset();
	body.setMassInv(0);
	body.setInertiaInv(PfxMatrix3(0));
	state.reset();
	state.setPosition(PfxVector3(0.0f, -2.5f, 0.0f));
	state.setMotionType(kPfxMotionTypeFixed);

	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	int id = rb_world->addRigidBody(state, body, collidable);
	SetColor(id, color);
	g_renderFlags[id] = true;
	return id;
}

// 物理オブジェクトの削除
void SDP::DestroyPhysicalObject(unsigned int id)
{
	--g_totalObjectNumber;
	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	rb_world->removeRigidBody(id);
	SetColor(id, GetColorU8(0, 0, 0, 0));
	g_physicsObjectMaterial[id].Diffuse = COLORF_ZERO;
	g_physicsObjectMaterial[id].Specular = COLORF_ZERO;
	g_physicsObjectMaterial[id].Ambient = COLORF_ZERO;
	g_physicsObjectMaterial[id].Emissive = COLORF_ZERO;
	g_physicsObjectMaterial[id].Power = 0.0f;

#if 0
	for (int i = 0; i < renderMeshs.size(); ++i)
	{
		if (renderMeshs[i].GetId() == id)
		{
			renderMeshs.erase(renderMeshs.begin() + i);
			break;
		}
	}
#endif

	for (int i = 0; i < g_renderMeshesID.size(); ++i)
	{
		if (g_renderMeshesID[i] == id)
		{
			g_renderMeshes.erase(g_renderMeshes.begin() + i);
			g_renderMeshesID.erase(g_renderMeshesID.begin() + i);
			break;
		}
	}

	for (int i = 0; i < CONVEX_MESH_MAX; ++i)
	{
		if (g_convexMeshesID[i] == id)
		{
			g_convexMeshes[i] = PfxConvexMesh();
			g_convexMeshesID[i] = ID_NULL;
			break;
		}
	}
}

// 不動ジョイントの設定
// 自動的に非接触オブジェクト化します
unsigned int SDP::AddPhysicalJointFixed(unsigned int obj1_id, unsigned int obj2_id, const VECTOR& point)
{
	PfxRigidBodyWorld* rb_world = &physicsGetWorld();

	PfxUInt32 id = 0;

	PfxRigidState& state1 = rb_world->getRigidState(obj1_id);
	PfxRigidState& state2 = rb_world->getRigidState(obj2_id);

	PfxFixJointInitParam jparam;
	jparam.anchorPoint = PfxVector3(point.x, point.y, -point.z);

	PfxJoint joint;
	pfxInitializeFixJoint(joint, state1, state2, jparam);
	id = rb_world->addJoint(joint);
	rb_world->appendNonContactPair(obj1_id, obj2_id);
	return id;
}

// ジョイントの削除
void SDP::DestroyJoint(unsigned int joint_id)
{
	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	rb_world->removeJoint(joint_id);
}

// メッシュデータのスケール設定
void SDP::InitScale(unsigned int vtxCnt, float* vtxData, float scale)
{
	for (int i = 0; i < vtxCnt; ++i)
	{
		vtxData[i * 6] *= scale;
		vtxData[i * 6 + 1] *= scale;
		vtxData[i * 6 + 2] *= scale;
	}
}

// 物理オブジェクト:球の描画
void RenderPhysicalSphere
	(unsigned int id, const PfxShape& shape, PfxTransform3& worldT)
{
	VERTEX3D vertex[NUM_SPHERE_VTX];
	float radius = shape.getSphere().m_radius;

	for (int idx = 0; idx < NUM_SPHERE_VTX; ++idx)
	{
		int idx_6 = idx * 6;
		PfxVector3 local_pos(sphere_vtx[idx_6] * radius, 
							 sphere_vtx[idx_6 + 1] * radius, 
							 sphere_vtx[idx_6 + 2] * radius);
		PfxVector3 world_vec = worldT * local_pos;

		PfxVector3 local_normal(sphere_vtx[idx_6 + 3], sphere_vtx[idx_6 + 4], sphere_vtx[idx_6 + 5]);
		PfxVector3 world_normal = worldT.getUpper3x3() * local_normal;

		vertex[idx].pos = VGet(world_vec.getX() + worldT.getTranslation().getX(), 
							   world_vec.getY() + worldT.getTranslation().getY(), 
							 -(world_vec.getZ() + worldT.getTranslation().getZ()));
		vertex[idx].norm = VGet(world_normal.getX(), world_normal.getY(), -world_normal.getZ());
		vertex[idx].dif = g_physicsObjectColor[id];
		vertex[idx].spc = GetColorU8(255, 255, 255, 255);
		vertex[idx].u = 0.0f;
		vertex[idx].v = 0.0f;
		vertex[idx].su = 0.0f;
		vertex[idx].sv = 0.0f;
	}

	DrawPolygonIndexed3D(vertex, NUM_SPHERE_VTX, sphere_idx, NUM_SPHERE_IDX / 3, DX_NONE_GRAPH, FALSE);
}

// 物理オブジェクト:箱の描画
void RenderPhysicalBox
	(unsigned int id, const PfxShape& shape, PfxTransform3& worldT)
{
	VERTEX3D vertex[NUM_BOX_VTX];
	PfxVector3 size = shape.getBox().m_half * 2.0f;

	for (int idx = 0; idx < NUM_BOX_VTX; ++idx)
	{
		int idx_6 = idx * 6;
		PfxVector3 local_pos(box_vtx[idx_6] * size.getX(), 
							 box_vtx[idx_6 + 1] * size.getY(), 
							 box_vtx[idx_6 + 2] * size.getZ());
		PfxVector3 world_vec = worldT * local_pos;

		PfxVector3 local_normal(box_vtx[idx_6 + 3], box_vtx[idx_6 + 4], box_vtx[idx_6 + 5]);
		PfxVector3 world_normal = worldT.getUpper3x3() * local_normal;

		vertex[idx].pos = VGet(world_vec.getX() + worldT.getTranslation().getX(),
							   world_vec.getY() + worldT.getTranslation().getY(),
							 -(world_vec.getZ() + worldT.getTranslation().getZ()));
		vertex[idx].norm = VGet(world_normal.getX(), world_normal.getY(), -world_normal.getZ());
		vertex[idx].dif = g_physicsObjectColor[id];
		vertex[idx].spc = GetColorU8(255, 255, 255, 255);
		vertex[idx].u = 0.0f;
		vertex[idx].v = 0.0f;
		vertex[idx].su = 0.0f;
		vertex[idx].sv = 0.0f;
	}

	DrawPolygonIndexed3D(vertex, NUM_BOX_VTX, box_idx, NUM_BOX_IDX / 3, DX_NONE_GRAPH, FALSE);
}

// 物理オブジェクト:筒の描画
void RenderPhysicalCylinder
	(unsigned int id, const PfxShape& shape, PfxTransform3& worldT)
{
	VERTEX3D vertex[NUM_CYLINDER_VTX];
	float length = shape.getCylinder().m_halfLen;
	float radius = shape.getCylinder().m_radius;

	for (int idx = 0; idx < NUM_CYLINDER_VTX; ++idx)
	{
		int idx_6 = idx * 6;
		PfxVector3 local_pos(cylinder_vtx[idx_6] * length, 
							 cylinder_vtx[idx_6 + 1] * radius, 
							 cylinder_vtx[idx_6 + 2] * radius);
		PfxVector3 world_vec = worldT * local_pos;

		PfxVector3 local_normal(cylinder_vtx[idx_6 + 3], cylinder_vtx[idx_6 + 4], cylinder_vtx[idx_6 + 5]);
		PfxVector3 world_normal = worldT.getUpper3x3() * local_normal;

		vertex[idx].pos = VGet(world_vec.getX() + worldT.getTranslation().getX(), 
							   world_vec.getY() + worldT.getTranslation().getY(), 
							 -(world_vec.getZ() + worldT.getTranslation().getZ()));
		vertex[idx].norm = VGet(world_normal.getX(), world_normal.getY(), -world_normal.getZ());
		vertex[idx].dif = g_physicsObjectColor[id];
		vertex[idx].spc = GetColorU8(255, 255, 255, 255);
		vertex[idx].u = 0.0f;
		vertex[idx].v = 0.0f;
		vertex[idx].su = 0.0f;
		vertex[idx].sv = 0.0f;
	}

	DrawPolygonIndexed3D(vertex, NUM_CYLINDER_VTX, cylinder_idx, NUM_CYLINDER_IDX / 3, DX_NONE_GRAPH, FALSE);
}


// 物理オブジェクト:カプセルの描画
void RenderPhysicalCapsule
	(unsigned int id, const PfxShape& shape, PfxTransform3& worldT)
{
	const PfxFloatInVec& radius = PfxFloatInVec(shape.getCapsule().m_radius);
	const PfxFloatInVec& half_length = PfxFloatInVec(shape.getCapsule().m_halfLen);

	PfxShape sphere_shape = shape;
	PfxSphere sphere(radius);
	sphere_shape.setSphere(sphere);

	PfxShape cylinder_shape = shape;
	PfxCylinder cylinder(half_length, radius);
	cylinder_shape.setCylinder(cylinder);

	PfxTransform3 tr1 = PfxTransform3::translation(PfxVector3(-half_length, 0.0f, 0.0f));
	tr1 = worldT * tr1;
	PfxTransform3 tr2 = PfxTransform3::translation(PfxVector3(half_length, 0.0f, 0.0f));
	tr2 = worldT * tr2;

	RenderPhysicalSphere(id, sphere_shape, tr1);
	RenderPhysicalSphere(id, sphere_shape, tr2);
	RenderPhysicalCylinder(id, cylinder_shape, worldT);
}

// 物理オブジェクト:メッシュの描画
void RenderPhysicslMesh(unsigned int id, const PfxShape& shape, PfxTransform3& worldT)
{
#if 0
	MeshDatas* mesh_datas = renderMeshs[0].GetMashDatas();
	for (int i = 0; i <= renderMeshs.size(); ++i)
	{
		if (i == renderMeshs.size()) return;

		if (renderMeshs[i].GetId() == id)
		{
			mesh_datas = renderMeshs[i].GetMashDatas();
			break;
		}
	}
#endif

	unsigned int mesh_id = 0;
	for (int i = 0; i <= g_renderMeshesID.size(); ++i)
	{
		if (i == g_renderMeshesID.size()) return;

		if (g_renderMeshesID[i] == id)
		{
			mesh_id = i;
			break;
		}
	}

	unsigned int vtx_cnt = g_renderMeshes[mesh_id]->GetVtxCnt();
	unsigned int idx_cnt = g_renderMeshes[mesh_id]->GetIdxCnt();
	float* vtx_data = g_renderMeshes[mesh_id]->GetVtxData();
	unsigned short* idx_data = g_renderMeshes[mesh_id]->GetIdxData();
	vector<VERTEX3D> vertex(vtx_cnt);

	for (int idx = 0; idx < vtx_cnt; ++idx)
	{
		int idx_6 = idx * 6;
		PfxVector3 local_pos(vtx_data[idx_6],
			vtx_data[idx_6 + 1],
			vtx_data[idx_6 + 2]);
		PfxVector3 world_vec = worldT * local_pos;

		PfxVector3 local_normal(vtx_data[idx_6 + 3], vtx_data[idx_6 + 4], vtx_data[idx_6 + 5]);
		PfxVector3 world_normal = worldT.getUpper3x3() * local_normal;

		vertex[idx].pos = VGet(world_vec.getX() + worldT.getTranslation().getX(),
			world_vec.getY() + worldT.getTranslation().getY(),
			-(world_vec.getZ() + worldT.getTranslation().getZ()));
		vertex[idx].norm = VGet(world_normal.getX(), world_normal.getY(), -world_normal.getZ());
		vertex[idx].dif = g_physicsObjectColor[id];
		vertex[idx].spc = GetColorU8(255, 255, 255, 255);
		vertex[idx].u = 0.0f;
		vertex[idx].v = 0.0f;
		vertex[idx].su = 0.0f;
		vertex[idx].sv = 0.0f;
	}

	DrawPolygonIndexed3D(&vertex[0], vtx_cnt, idx_data, idx_cnt / 3, DX_NONE_GRAPH, FALSE);
}

// 物理オブジェクト描画
void SDP::RenderPhysicalObject()
{
	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	for (int id = 0;id < (int)rb_world->getRigidBodyCount();id++) {
		if (rb_world->isRemovedRigidBody(id)) continue;
		if (!g_renderFlags[id]) continue;

		const PfxRigidState& state = rb_world->getRigidState(id);
		const PfxCollidable& coll = rb_world->getCollidable(id);

		PfxTransform3 rbT(state.getOrientation(), state.getPosition());

		PfxShapeIterator itrShape(coll);
		for (int j = 0;j < (int)coll.getNumShapes();j++, ++itrShape) {
			const PfxShape& shape = *itrShape;
			PfxTransform3 offsetT = shape.getOffsetTransform();
			PfxTransform3 worldT = rbT * offsetT;

			SetMaterialParam(g_physicsObjectMaterial[id]);

			switch (shape.getType()) {
			case kPfxShapeSphere:
				RenderPhysicalSphere(id, shape, worldT);
				break;

			case kPfxShapeBox:
				RenderPhysicalBox(id, shape, worldT);
				break;

			case kPfxShapeCapsule:
				RenderPhysicalCapsule(id, shape, worldT);
				break;

			case kPfxShapeCylinder:
				RenderPhysicalCylinder(id, shape, worldT);
				break;

			case kPfxShapeConvexMesh:
				RenderPhysicslMesh(id, shape, worldT);
				break;

			case kPfxShapeLargeTriMesh:
				RenderPhysicslMesh(id, shape, worldT);
				break;

			default:
				break;
			}
		}
	}
}

// 物理オブジェクトの表示・非表示設定
void SDP::SetRenderFlag(unsigned int id, bool flag)
{
	g_renderFlags[id] = flag;
}

// 物理オブジェクトの表示・非表示取得
bool SDP::GetRenderFlag(unsigned int id)
{
	return g_renderFlags[id];
}

// 総オブジェクト数の取得
unsigned int SDP::GetTotalObjectNumber()
{
	return g_totalObjectNumber;
}

// 物理オブジェクトの座標設定
void SDP::SetPosition(unsigned int id, const VECTOR& pos)
{
	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	PfxRigidState& state = rb_world->getRigidState(id);
	state.setPosition(PfxVector3(pos.x, pos.y, -pos.z));
}

// 物理オブジェクトの座標取得
VECTOR SDP::GetPosition(unsigned int id)
{
	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	PfxRigidState& state = rb_world->getRigidState(id);
	PfxVector3 pos = state.getPosition();
	return VGet(pos.getX(), pos.getY(), -pos.getZ());
}

// 物理オブジェクトの回転設定
void SDP::SetRotate(unsigned int id, const VECTOR& rotate)
{
	// DxLibのVectorからGamePhysicsSDKのクオータニオンに変換
	float rx = rotate.x * 0.5f * SCE_PFX_PI / 180.0f;
	float ry = rotate.y * 0.5f * SCE_PFX_PI / 180.0f;
	float rz = -rotate.z * 0.5f * SCE_PFX_PI / 180.0f;

	float cx = cosf(rx);
	float sx = sinf(rx);
	float cy = cosf(ry);
	float sy = sinf(ry);
	float cz = cosf(rz);
	float sz = sinf(rz);

	PfxQuat orientation(
		sx * cy * cz - cx * sy * sz,
		cx * sy * cz + sx * cy * sz,
		cx * cy * sz - sx * sy * cz,
		cx * cy * cz + sx * sy * sz
	);

	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	PfxRigidState& state = rb_world->getRigidState(id);
	state.setOrientation(orientation);
}

// 物理オブジェクトの回転取得
VECTOR SDP::GetRotate(unsigned int id)
{
	// GamePhysicsSDKのクオータニオンからDxLibのVectorに変換
	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	PfxRigidState& state = rb_world->getRigidState(id);
	PfxQuat orientation = state.getOrientation();

	float sinr_cosp = 2.0f * (orientation.getW() * orientation.getX() + orientation.getY() * orientation.getZ());
	float cosr_cosp = 1.0f - 2.0f * (orientation.getX() * orientation.getX() + orientation.getY() * orientation.getY());
	float rx = atan2f(sinr_cosp, cosr_cosp);

	float sinp = 2.0f * (orientation.getW() * orientation.getY() - orientation.getZ() * orientation.getX());
	float ry = 0.0f;

	if (fabsf(sinp) >= 1.0f)
	{
		ry = copysignf(SCE_PFX_PI * 0.5f, sinp);
	}
	else
	{
		ry = asinf(sinp);
	}

	float siny_cosp = 2.0f * (orientation.getW() * orientation.getZ() + orientation.getX() * orientation.getY());
	float cosy_cosp = 1.0f - 2.0f * (orientation.getY() * orientation.getY() + orientation.getZ() * orientation.getZ());
	float rz = atan2f(siny_cosp, cosy_cosp);

	// ラジアン -> 度
	rx *= 180.0f / SCE_PFX_PI;
	ry *= 180.0f / SCE_PFX_PI;
	rz *= 180.0f / SCE_PFX_PI;

	return VGet(rx, ry, -rz);
}

// 物理オブジェクトの向き取得
VECTOR SDP::GetDirection(unsigned int id, const VECTOR& std_vec)
{
	PfxVector3 vec = PfxVector3(std_vec.x, std_vec.y, -std_vec.z);

	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	PfxRigidState& state = rb_world->getRigidState(id);
	PfxQuat q = state.getOrientation();

	PfxVector3 qv(q.getX(), q.getY(), q.getZ());
	PfxVector3 t = 2.0f * cross(qv, vec);

	vec = vec + q.getW() * t + cross(qv, t);
	VECTOR re_vec = VGet(vec.getX(), vec.getY(), -vec.getZ());
	re_vec = VNorm(re_vec);
	return re_vec;
}

// ディフューズカラーをアンビエントカラーに変換
COLOR_F Color2Ambient(const COLOR_U8& color)
{
	return GetColorF((float)color.r / 255.0f * AMBIENT_MULTIPLIER,
		(float)color.g / 255.0f * AMBIENT_MULTIPLIER,
		(float)color.b / 255.0f * AMBIENT_MULTIPLIER, 0.0f);
}

// 物理オブジェクトの色設定
void SDP::SetColor(unsigned int id, const COLOR_U8& color)
{
	g_physicsObjectColor[id] = color;
	SetAmbient(id, Color2Ambient(color));
}

// 物理オブジェクトのアンビエントカラー設定
void SDP::SetAmbient(unsigned int id, const COLOR_F& amb)
{
	g_physicsObjectMaterial[id].Diffuse = COLORF_ZERO;
	g_physicsObjectMaterial[id].Specular = COLORF_ZERO;
	g_physicsObjectMaterial[id].Ambient = amb;
	g_physicsObjectMaterial[id].Emissive = COLORF_ZERO;
	g_physicsObjectMaterial[id].Power = MATERIAL_POWER;
}

// 物理オブジェクトの並進速度設定
void SDP::SetLinerVelocity(unsigned int id, const VECTOR& vec)
{
	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	PfxRigidState& state = rb_world->getRigidState(id);
	state.setLinearVelocity(PfxVector3(vec.x, vec.y, -vec.z));
}

// 物理オブジェクトの回転速度設定
void SDP::SetAngularVelocity(unsigned int id, const VECTOR& vec)
{
	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	PfxRigidState& state = rb_world->getRigidState(id);
	state.setAngularVelocity(PfxVector3(vec.x, vec.y, -vec.z));
}

// 物理オブジェクトの並進速度取得
VECTOR SDP::GetLinerVelocity(unsigned int id)
{
	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	PfxRigidState& state = rb_world->getRigidState(id);
	PfxVector3 liner_velocity = state.getLinearVelocity();
	return VGet(liner_velocity.getX(), liner_velocity.getY(), liner_velocity.getZ());
}

// 物理オブジェクトの回転速度取得
VECTOR SDP::GetAngularVelocity(unsigned int id)
{
	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	PfxRigidState& state = rb_world->getRigidState(id);
	PfxVector3 angular_velocity = state.getAngularVelocity();
	return VGet(angular_velocity.getX(), angular_velocity.getY(), angular_velocity.getZ());
}

// 物理オブジェクトの質量設定
void SDP::SetMass(unsigned int id, float mass)
{
	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	PfxRigidBody& body = rb_world->getRigidBody(id);
	body.setMass(mass);
}

// 物理オブジェクトの逆質量設定
void SDP::SetMassInv(unsigned int id, float inv_mass)
{
	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	PfxRigidBody& body = rb_world->getRigidBody(id);
	body.setMassInv(inv_mass);
}

// 物理オブジェクトの質量取得
float SDP::GetMass(unsigned int id)
{
	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	PfxRigidBody& body = rb_world->getRigidBody(id);
	return body.getMass();
}

// 物理オブジェクトの逆質量取得
float SDP::GetMassInv(unsigned int id)
{
	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	PfxRigidBody& body = rb_world->getRigidBody(id);
	return body.getMassInv();
}

// 物理オブジェクトの摩擦設定
void SDP::SetFriction(unsigned int id, float fric)
{
	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	PfxRigidBody& body = rb_world->getRigidBody(id);
	body.setFriction(fric);
}

// 物理オブジェクトの摩擦取得
float SDP::GetFriction(unsigned int id)
{
	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	PfxRigidBody& body = rb_world->getRigidBody(id);
	return body.getFriction();
}

// 物理オブジェクトの反発係数設定
void SDP::SetRestitution(unsigned int id, float elastic)
{
	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	PfxRigidBody& body = rb_world->getRigidBody(id);
	body.setRestitution(elastic);
}

// 物理オブジェクトの反発係数取得
float SDP::GetRestitution(unsigned int id) 
{
	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	PfxRigidBody& body = rb_world->getRigidBody(id);
	return body.getRestitution();
}

// 物理オブジェクトの接触判定
bool SDP::IsContact(unsigned int objid_a, unsigned int objid_b)
{
	PfxRigidBodyWorld* rb_world = &physicsGetWorld();

	for (int i = 0; i < rb_world->getContactCount(); ++i)
	{
		const PfxContactManifold& contact = rb_world->getContactManifold(i);

		if (contact.getNumContacts() <= 0)
		{
			continue;
		}

		int rbid_a = contact.getRigidBodyIdA();
		int rbid_b = contact.getRigidBodyIdB();

		if ((rbid_a == objid_a && rbid_b == objid_b) || (rbid_a == objid_b && rbid_b == objid_a))
		{
			return true;
		}
	}

	return false;
}

// 物理オブジェクトの非接触設定
void SDP::SetNonContactPair(unsigned int obj1_id, unsigned int obj2_id)
{
	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	rb_world->appendNonContactPair(obj1_id, obj2_id);
}

// 物理オブジェクトの非接触解除
void SDP::ReleaseNonContactPair(unsigned int obj1_id, unsigned int obj2_id)
{
	PfxRigidBodyWorld* rb_world = &physicsGetWorld();
	rb_world->removeNonContactPair(obj1_id, obj2_id);
}

// 物理オブジェクト用メッシュデータのレンダリング
// 物理演算・当たり判定は無し 単に確認等のための表示
void SDP::RenderSDPMesh(const VECTOR& pos, MeshDatas* datas, const COLOR_U8& color)
{
	unsigned int vtx_cnt = datas->GetVtxCnt();
	unsigned int idx_cnt = datas->GetIdxCnt();
	float* vtx_data = datas->GetVtxData();
	unsigned short* idx_data = datas->GetIdxData();
	vector<VERTEX3D> vertex(vtx_cnt);

	for (int idx = 0; idx < vtx_cnt; ++idx)
	{
		int idx_6 = idx * 6;
		
		vertex[idx].pos = VGet(pos.x + vtx_data[idx_6], pos.y + vtx_data[idx_6 + 1], pos.z + vtx_data[idx_6 + 2]);
		vertex[idx].norm = VGet(vtx_data[idx_6 + 3], vtx_data[idx_6 + 4], vtx_data[idx_6 + 5]);
		vertex[idx].dif = color;
		vertex[idx].spc = GetColorU8(255, 255, 255, 255);
		vertex[idx].u = 0.0f;
		vertex[idx].v = 0.0f;
		vertex[idx].su = 0.0f;
		vertex[idx].sv = 0.0f;
	}

	DrawPolygonIndexed3D(&vertex[0], vtx_cnt, idx_data, idx_cnt / 3, DX_NONE_GRAPH, FALSE);
}
