/*
Physics Effects Copyright(C) 2012 Sony Computer Entertainment Inc.
All rights reserved.

Physics Effects is open software; you can redistribute it and/or
modify it under the terms of the BSD License.

Physics Effects is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the BSD License for more details.

A copy of the BSD License is distributed with
Physics Effects under the filename: physics_effects_license.txt
*/

/*
	※変更有　createSceneLandscape関数の内部処理をコメントアウト
*/

///////////////////////////////////////////////////////////////////////////////
// Simulation Headers

#include "physics_func.h"
//#include "../GamePhysicsSdk/extra/physics_effects/common/render_func.h"
//#include "../GamePhysicsSdk/extra/physics_effects/common/create_render_mesh.h"

#ifdef ENABLE_DEBUG_DRAW
	extern PfxDebugRender *g_debugRender;
#endif

///////////////////////////////////////////////////////////////////////////////
// Simulation Data

#define NUM_RAYS 50

static int pickJointId = -1;
static int raycastObjId = -1;
static int sSceneId;

//J プールメモリ
//E Pool memory
static PfxUInt32 poolBytes;
static void *poolBuff;

//E World
PfxRigidBodyWorld* rbWorld;

//J ラージメッシュ
//E Large mesh
//#include "town.h"
static PfxArray<PfxLargeTriMesh*>	*largeMeshes;
static PfxArray<PfxConvexMesh*>		*convexMeshes;

//J 描画メッシュ
//E Render meshes
static PfxMap<void*,int> *renderMeshes;

//J レイ
//E Ray
PfxRayInput SCE_PFX_ALIGNED(128) rayInputs[NUM_RAYS];
PfxRayOutput SCE_PFX_ALIGNED(128) rayOutputs[NUM_RAYS];
static int numRays = 0;

// Area
PfxVector3 areaCenter;
PfxVector3 areaExtent;

///////////////////////////////////////////////////////////////////////////////
// Create Scene

int createBrick(const PfxVector3 &pos,const PfxQuat &rot,const PfxVector3 &boxSize,PfxFloat mass)
{
	PfxRigidState state;
	PfxRigidBody body;
	PfxCollidable collidable;
	
	PfxBox box(boxSize);
	PfxShape shape;
	shape.reset();
	shape.setBox(box);
	collidable.reset();
	collidable.addShape(shape);
	collidable.finish();
	body.reset();
	body.setRestitution(0.0f);
	body.setMass(mass);
	body.setInertia(pfxCalcInertiaBox(boxSize,mass));
	state.reset();
	state.setPosition(pos);
	state.setOrientation(rot);
	state.setMotionType(kPfxMotionTypeActive);
	state.setUseSleep(1);

	return rbWorld->addRigidBody(state,body,collidable);
}


void createWall(const PfxVector3 &offsetPosition,int stackSize,const PfxVector3 &boxSize)
{
	PfxFloat bodyMass = 0.5f;

	//PfxFloat diffX = boxSize[0] * 1.02f;
	PfxFloat diffY = boxSize[1] * 1.02f;
	PfxFloat diffZ = boxSize[2] * 1.02f;

	PfxFloat offset = -stackSize * (diffZ * 2.0f) * 0.5f;
	PfxVector3 pos(0.0f, diffY, 0.0f);

	while(stackSize) {
		for(int i=0;i<stackSize;i++) {
			pos[2] = offset + (PfxFloat)i * (diffZ * 2.0f);
		
			createBrick(offsetPosition+pos,PfxQuat::identity(),boxSize,bodyMass);
		}
		offset += diffZ;
		pos[1] += (diffY * 2.0f);
		stackSize--;
	}
}

void createPyramid(const PfxVector3 &offsetPosition,int stackSize,const PfxVector3 &boxSize)
{
	PfxFloat space = 0.0001f;
	PfxVector3 pos(0.0f, boxSize[1], 0.0f);

	PfxFloat diffX = boxSize[0] * 1.02f;
	PfxFloat diffY = boxSize[1] * 1.02f;
	PfxFloat diffZ = boxSize[2] * 1.02f;

	PfxFloat offsetX = -stackSize * (diffX * 2.0f + space) * 0.5f;
	PfxFloat offsetZ = -stackSize * (diffZ * 2.0f + space) * 0.5f;
	while(stackSize) {
		for(int j=0;j<stackSize;j++) {
			pos[2] = offsetZ + (PfxFloat)j * (diffZ * 2.0f + space);
			for(int i=0;i<stackSize;i++) {
				pos[0] = offsetX + (PfxFloat)i * (diffX * 2.0f + space);
				createBrick(offsetPosition+pos,PfxQuat::identity(),boxSize,1.0f);
			}
		}
		offsetX += diffX;
		offsetZ += diffZ;
		pos[1] += (diffY * 2.0f + space);
		stackSize--;
	}
}

void createTowerCircle(const PfxVector3 &offsetPosition,int stackSize,int rotSize,const PfxVector3 &boxSize)
{
	PfxFloat radius = 1.3f * rotSize * boxSize[0] / SCE_PFX_PI;

	// create active boxes
	PfxQuat rotY = PfxQuat::identity();
	PfxFloat posY = boxSize[1];

	for(int i=0;i<stackSize;i++) {
		for(int j=0;j<rotSize;j++) {
			createBrick(offsetPosition+rotate(rotY,PfxVector3(0.0f , posY, radius)),rotY,boxSize,0.5f);

			rotY *= PfxQuat::rotationY(SCE_PFX_PI/(rotSize*0.5f));
		}

		posY += boxSize[1] * 2.0f;
		rotY *= PfxQuat::rotationY(SCE_PFX_PI/(PfxFloat)rotSize);
	}
}

void createScenePrimitives()
{
	PfxRigidState state;
	PfxRigidBody body;
	PfxCollidable collidable;

	// sphere
	{
		PfxSphere sphere(1.0f);
		PfxShape shape;
		shape.reset();
		shape.setSphere(sphere);
		collidable.reset();
		collidable.addShape(shape);
		collidable.finish();
		body.reset();
		body.setMass(1.0f);
		body.setInertia(pfxCalcInertiaSphere(1.0f,1.0f));
		state.reset();
		state.setPosition(PfxVector3(-5.0f,5.0f,0.0f));
		state.setMotionType(kPfxMotionTypeActive);
		state.setUseSleep(1);

		rbWorld->addRigidBody(state,body,collidable);
	}

	// box
	{
		PfxBox box(1.0f,1.0f,1.0f);
		PfxShape shape;
		shape.reset();
		shape.setBox(box);
		collidable.reset();
		collidable.addShape(shape);
		collidable.finish();
		body.reset();
		body.setMass(1.0f);
		body.setInertia(pfxCalcInertiaBox(PfxVector3(1.0f),1.0f));
		state.reset();
		state.setPosition(PfxVector3(0.0f,5.0f,5.0f));
		state.setMotionType(kPfxMotionTypeActive);
		state.setUseSleep(1);

		rbWorld->addRigidBody(state,body,collidable);
	}

	// capsule
	{
		PfxCapsule capsule(1.5f,0.5f);
		PfxShape shape;
		shape.reset();
		shape.setCapsule(capsule);
		collidable.reset();
		collidable.addShape(shape);
		collidable.finish();
		body.reset();
		body.setMass(2.0f);
		body.setInertia(pfxCalcInertiaCylinderX(2.0f,0.5f,2.0f));
		state.reset();
		state.setPosition(PfxVector3(5.0f,5.0f,0.0f));
		state.setMotionType(kPfxMotionTypeActive);
		state.setUseSleep(1);

		rbWorld->addRigidBody(state,body,collidable);
	}

	// cylinder
	{
		PfxCylinder cylinder(0.5f,1.5f);
		PfxShape shape;
		shape.reset();
		shape.setCylinder(cylinder);
		collidable.reset();
		collidable.addShape(shape);
		collidable.finish();
		body.reset();
		body.setMass(3.0f);
		body.setInertia(pfxCalcInertiaCylinderX(0.5f,1.5f,3.0f));
		state.reset();
		state.setPosition(PfxVector3(0.0f,10.0f,0.0f));
		state.setMotionType(kPfxMotionTypeActive);
		state.setUseSleep(1);

		rbWorld->addRigidBody(state,body,collidable);
	}

	// combined primitives
	{
		//J	複合剛体を作成する場合は、ワールド内のバッファに形状を格納するため
		//J	setupCollidable()メソッドを呼び出し、必要な分のPfxShapeを割り当てる。
		//J	リリースはPfxRigidBodyWorldによって自動的に行われる。
		//E To create a combined shape, call setupCollidable() to assign enough buffers of PfxShape.
		//E These buffers are automatically released by PfxRigidBodyWorld.

		rbWorld->setupCollidable(collidable,3);
		{
			PfxBox box(0.5f,0.5f,1.5f);
			PfxShape shape;
			shape.reset();
			shape.setBox(box);
			shape.setOffsetPosition(PfxVector3(-2.0f,0.0f,0.0f));
			collidable.addShape(shape);
		}
		{
			PfxBox box(0.5f,1.5f,0.5f);
			PfxShape shape;
			shape.reset();
			shape.setBox(box);
			shape.setOffsetPosition(PfxVector3(2.0f,0.0f,0.0f));
			collidable.addShape(shape);
		}
		{
			PfxCapsule cap(1.5f,0.5f);
			PfxShape shape;
			shape.reset();
			shape.setCapsule(cap);
			collidable.addShape(shape);
		}
		collidable.finish();
		body.reset();
		body.setMass(3.0f);
		body.setInertia(pfxCalcInertiaBox(PfxVector3(2.5f,1.0f,1.0f),3.0f));
		state.reset();
		state.setPosition(PfxVector3(0.0f,5.0f,0.0f));
		state.setMotionType(kPfxMotionTypeActive);
		state.setUseSleep(1);

		rbWorld->addRigidBody(state,body,collidable);
	}
}

void createSceneBoxGround()
{
	PfxRigidState state;
	PfxRigidBody body;
	PfxCollidable collidable;
	
	PfxBox box(150.0f,2.5f,150.0f);
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
	state.setPosition(PfxVector3(0.0f,-2.5f,0.0f));
	state.setMotionType(kPfxMotionTypeFixed);

	rbWorld->addRigidBody(state,body,collidable);
}

void createSceneLandscape(const PfxVector3 &pos)
{
#if 0
	PfxLargeTriMesh* pLargeMesh = (PfxLargeTriMesh*)SCE_PFX_UTIL_ALLOC(16,sizeof(PfxLargeTriMesh));
	SCE_PFX_ALWAYS_ASSERT(pLargeMesh);
	memset(pLargeMesh,0,sizeof(PfxLargeTriMesh));
	
	PfxCreateLargeTriMeshParam param;

	param.verts = LargeMeshVtx;
	param.numVerts = LargeMeshVtxCount;
	param.vertexStrideBytes = sizeof(float)*6;

	param.triangles = LargeMeshIdx;
	param.numTriangles = LargeMeshIdxCount/3;
	param.triangleStrideBytes = sizeof(unsigned short)*3;

	// Calculate thickness automatically
	//param.flag |= SCE_PFX_MESH_FLAG_AUTO_THICKNESS;
	//param.defaultThickness = 0.25f;

	// Use quantized value for vertices and facets
	param.flag |= SCE_PFX_MESH_FLAG_USE_QUANTIZED;

	// Use bvh structure
	param.flag |= SCE_PFX_MESH_FLAG_USE_BVH;

	// Print large mesh info
	param.flag |= SCE_PFX_MESH_FLAG_OUTPUT_INFO;

	// Apply user data
	param.userData = (PfxUInt32*)SCE_PFX_UTIL_ALLOC(16,sizeof(PfxUInt32)*LargeMeshIdxCount/3);
	for(int i=0;i<LargeMeshIdxCount/3;i++) {
		param.userData[i] = i;
	}

	PfxInt32 ret = pfxCreateLargeTriMesh(*pLargeMesh,param);
	if(ret != SCE_PFX_OK) {
		SCE_PFX_PRINTF("Can't create large mesh. err = 0x%x\n",ret);
		SCE_PFX_ALWAYS_ASSERT(ret == SCE_PFX_OK);
	}

	SCE_PFX_UTIL_FREE(param.userData);

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
	state.reset();
	state.setPosition(pos);
	state.setMotionType(kPfxMotionTypeFixed);
	world->addRigidBody(state,body,collidable);
	
	largeMeshes->push(pLargeMesh);

	int renderMeshId = createRenderMesh(pLargeMesh);
	renderMeshes->insert(pLargeMesh,renderMeshId);
#endif
}

void createSceneStacking()
{
	// stacking boxes (bench)
	//createWall(PfxVector3(0.0f,0.0f,0.0f),10,PfxVector3(1));
	createTowerCircle(PfxVector3(0.0f,0.0f,0.0f),8,24,PfxVector3(1.0f));
}

void createSceneFalling()
{
	int size = 6;
	const float cubeSize = 0.5f;
	float spacing = cubeSize * 10.0f;
	PfxVector3 pos(0.0f, cubeSize * 2, 0.0f);
	float offset = -size * (cubeSize * 2.0f + spacing) * 0.5f;

	for(int k=0;k<3;k++) {
		for(int j=0;j<size;j++) {
			pos[2] = offset + (float)j * (cubeSize * 2.0f + spacing);
			for(int i=0;i<size;i++) {
				pos[0] = offset + (float)i * (cubeSize * 2.0f + spacing);
				createBrick(pos,PfxQuat::identity(),PfxVector3(cubeSize),1.0f);
			}
		}
		offset -= 0.05f * spacing * (size-1);
		spacing *= 1.01f;
		pos[1] += (cubeSize * 2.0f + spacing);
	}
}

void createSceneFallingPrimitives()
{
	int size = 6;
	const float cubeSize = 0.5f;
	float spacing = cubeSize * 10.0f;
	PfxVector3 pos(0.0f, cubeSize * 2, 0.0f);
	float offset = -size * (cubeSize * 2.0f + spacing) * 0.5f;

	srand(1234);

	for(int k=0;k<3;k++) {
		for(int j=0;j<size;j++) {
			pos[2] = offset + (float)j * (cubeSize * 2.0f + spacing);
			for(int i=0;i<size;i++) {
				pos[0] = offset + (float)i * (cubeSize * 2.0f + spacing);

				int primType = rand() % 4;

				{
					PfxRigidState state;
					PfxRigidBody body;
					PfxCollidable collidable;

					switch(primType) {
						case 0:// sphere
						{
							PfxSphere sphere(cubeSize);
							PfxShape shape;
							shape.reset();
							shape.setSphere(sphere);
							collidable.reset();
							collidable.addShape(shape);
							collidable.finish();
							body.reset();
							body.setMass(1.0f);
							body.setInertia(pfxCalcInertiaSphere(cubeSize,1.0f));
						}
						break;

						case 1:// box
						{
							PfxBox box(cubeSize,cubeSize,cubeSize);
							PfxShape shape;
							shape.reset();
							shape.setBox(box);
							collidable.reset();
							collidable.addShape(shape);
							collidable.finish();
							body.reset();
							body.setMass(1.0f);
							body.setInertia(pfxCalcInertiaBox(PfxVector3(cubeSize),1.0f));
						}
						break;

						case 2:// capsule
						{
							PfxCapsule capsule(cubeSize,cubeSize*0.5f);
							PfxShape shape;
							shape.reset();
							shape.setCapsule(capsule);
							collidable.reset();
							collidable.addShape(shape);
							collidable.finish();
							body.reset();
							body.setMass(1.0f);
							body.setInertia(pfxCalcInertiaCylinderX(2.0f*cubeSize,cubeSize,1.0f));
						}
						break;

						case 3:// cylinder
						{
							PfxCylinder cylinder(cubeSize*0.5f,cubeSize);
							PfxShape shape;
							shape.reset();
							shape.setCylinder(cylinder);
							collidable.reset();
							collidable.addShape(shape);
							collidable.finish();
							body.reset();
							body.setMass(1.0f);
							body.setInertia(pfxCalcInertiaCylinderX(cubeSize,cubeSize*2.0f,1.0f));
						}
						break;
					}

					state.reset();
					state.setPosition(pos);
					state.setMotionType(kPfxMotionTypeActive);
					state.setUseSleep(1);

					int rb = rbWorld->addRigidBody(state,body,collidable);
				}
			}
		}
		offset -= 0.05f * spacing * (size-1);
		spacing *= 1.01f;
		pos[1] += (cubeSize * 2.0f + spacing);
	}
}

void createSceneRagdoll(const PfxVector3 &offsetPosition,const PfxQuat &offsetOrientation)
{
	PfxUInt32 head,torso,chest,
		upperLegL,lowerLegL,upperArmL,lowerArmL,
		upperLegR,lowerLegR,upperArmR,lowerArmR;
	
	// Adjust inertia
	PfxFloat inertiaScale = 3.0f;

	PfxRigidState state;
	PfxRigidBody body;
	PfxCollidable collidable;

	// Head
	{
		PfxSphere sphere(0.3f);
		PfxShape shape;
		shape.reset();
		shape.setSphere(sphere);
		collidable.reset();
		collidable.addShape(shape);
		collidable.finish();
		body.reset();
		body.setMass(3.0f);
		body.setInertia(inertiaScale * pfxCalcInertiaSphere(0.3f,3.0f));
		state.reset();
		state.setPosition(offsetPosition + rotate(offsetOrientation,PfxVector3(0.0f,3.38433f,0.0f)));
		state.setOrientation(offsetOrientation);
		state.setMotionType(kPfxMotionTypeActive);
		state.setUseSleep(1);
		head = rbWorld->addRigidBody(state,body,collidable);
	}
	
	// Torso
	{
		PfxSphere sphere(0.35f);
		PfxShape shape;
		shape.reset();
		shape.setSphere(sphere);
		collidable.reset();
		collidable.addShape(shape);
		collidable.finish();
		body.reset();
		body.setMass(10.0f);
		body.setInertia(inertiaScale * pfxCalcInertiaSphere(0.35f,10.0f));
		state.reset();
		state.setPosition(offsetPosition + rotate(offsetOrientation,PfxVector3(0.0f,1.96820f,0.0f)));
		state.setOrientation(offsetOrientation);
		state.setMotionType(kPfxMotionTypeActive);
		state.setUseSleep(1);
		torso = rbWorld->addRigidBody(state,body,collidable);
	}

	// Chest
	{
		PfxCapsule capsule(0.1f,0.38f);
		PfxShape shape;
		shape.reset();
		shape.setOffsetOrientation(PfxQuat(0.0f,0.0f,0.70711f,0.70711f));
		shape.setCapsule(capsule);
		collidable.reset();
		collidable.addShape(shape);
		collidable.finish();
		body.reset();
		body.setMass(8.0f);
		body.setInertia(inertiaScale * pfxCalcInertiaCylinderY(0.1f+0.38f,0.38f,8.0f));
		state.reset();
		state.setPosition(offsetPosition + rotate(offsetOrientation,PfxVector3(0.0f,2.66926f,0.0f)));
		state.setOrientation(offsetOrientation);
		state.setMotionType(kPfxMotionTypeActive);
		state.setUseSleep(1);
		chest = rbWorld->addRigidBody(state,body,collidable);
	}

	// UpperLegL
	{
		PfxCapsule capsule(0.35f,0.15f);
		PfxShape shape;
		shape.reset();
		shape.setOffsetOrientation(PfxQuat(0.0f,0.0f,0.70711f,0.70711f));
		shape.setCapsule(capsule);
		collidable.reset();
		collidable.addShape(shape);
		collidable.finish();
		body.reset();
		body.setMass(8.0f);
		body.setInertia(inertiaScale * pfxCalcInertiaCylinderY(0.35f+0.15f,0.15f,8.0f));
		state.reset();
		state.setPosition(offsetPosition + rotate(offsetOrientation,PfxVector3(0.21f,1.34871f,0.0f)));
		state.setOrientation(offsetOrientation);
		state.setMotionType(kPfxMotionTypeActive);
		state.setUseSleep(1);
		upperLegL = rbWorld->addRigidBody(state,body,collidable);
	}

	// LowerLegL
	{
		PfxCapsule capsule(0.3f,0.15f);
		PfxShape shape;
		shape.reset();
		shape.setOffsetOrientation(PfxQuat(0.0f,0.0f,0.70711f,0.70711f));
		shape.setCapsule(capsule);
		collidable.reset();
		collidable.addShape(shape);
		collidable.finish();
		body.reset();
		body.setMass(4.0f);
		body.setInertia(inertiaScale * pfxCalcInertiaCylinderY(0.3f+0.15f,0.15f,4.0f));
		state.reset();
		state.setPosition(offsetPosition + rotate(offsetOrientation,PfxVector3(0.21f,0.59253f,0.0f)));
		state.setOrientation(offsetOrientation);
		state.setMotionType(kPfxMotionTypeActive);
		state.setUseSleep(1);
		lowerLegL = rbWorld->addRigidBody(state,body,collidable);
	}

	// UpperArmL
	{
		PfxCapsule capsule(0.25f,0.15f);
		PfxShape shape;
		shape.reset();
		shape.setOffsetOrientation(PfxQuat(0.0f,0.0f,0.70711f,0.70711f));
		shape.setCapsule(capsule);
		collidable.reset();
		collidable.addShape(shape);
		collidable.finish();
		body.reset();
		body.setMass(5.0f);
		body.setInertia(inertiaScale * pfxCalcInertiaCylinderY(0.25f+0.15f,0.15f,5.0f));
		state.reset();
		state.setPosition(offsetPosition + rotate(offsetOrientation,PfxVector3(0.72813f,2.87483f,0.0f)));
		state.setOrientation(offsetOrientation * PfxQuat(0.0f,0.0f,0.70711f,0.70711f));
		state.setMotionType(kPfxMotionTypeActive);
		state.setUseSleep(1);
		upperArmL = rbWorld->addRigidBody(state,body,collidable);
	}

	// LowerArmL
	{
		PfxCapsule capsule(0.225f,0.15f);
		PfxShape shape;
		shape.reset();
		shape.setOffsetOrientation(PfxQuat(0.0f,0.0f,0.70711f,0.70711f));
		shape.setCapsule(capsule);
		collidable.reset();
		collidable.addShape(shape);
		collidable.finish();
		body.reset();
		body.setMass(3.0f);
		body.setInertia(inertiaScale * pfxCalcInertiaCylinderY(0.225f+0.15f,0.15f,3.0f));
		state.reset();
		state.setPosition(offsetPosition + rotate(offsetOrientation,PfxVector3(1.42931f,2.87483f,0.0f)));
		state.setOrientation(offsetOrientation * PfxQuat(0.0f,0.0f,0.70711f,0.70711f));
		state.setMotionType(kPfxMotionTypeActive);
		state.setUseSleep(1);
		lowerArmL = rbWorld->addRigidBody(state,body,collidable);
	}

	// UpperLegR
	{
		PfxCapsule capsule(0.35f,0.15f);
		PfxShape shape;
		shape.reset();
		shape.setOffsetOrientation(PfxQuat(0.0f,0.0f,0.70711f,0.70711f));
		shape.setCapsule(capsule);
		collidable.reset();
		collidable.addShape(shape);
		collidable.finish();
		body.reset();
		body.setMass(8.0f);
		body.setInertia(inertiaScale * pfxCalcInertiaCylinderY(0.35f+0.15f,0.15f,8.0f));
		state.reset();
		state.setPosition(offsetPosition + rotate(offsetOrientation,PfxVector3(-0.21f,1.34871f,0.0f)));
		state.setOrientation(offsetOrientation);
		state.setMotionType(kPfxMotionTypeActive);
		state.setUseSleep(1);
		upperLegR = rbWorld->addRigidBody(state,body,collidable);
	}

	// LowerLegR
	{
		PfxCapsule capsule(0.3f,0.15f);
		PfxShape shape;
		shape.reset();
		shape.setOffsetOrientation(PfxQuat(0.0f,0.0f,0.70711f,0.70711f));
		shape.setCapsule(capsule);
		collidable.reset();
		collidable.addShape(shape);
		collidable.finish();
		body.reset();
		body.setMass(4.0f);
		body.setInertia(inertiaScale * pfxCalcInertiaCylinderY(0.3f+0.15f,0.15f,4.0f));
		state.reset();
		state.setPosition(offsetPosition + rotate(offsetOrientation,PfxVector3(-0.21f,0.59253f,0.0f)));
		state.setOrientation(offsetOrientation);
		state.setMotionType(kPfxMotionTypeActive);
		state.setUseSleep(1);
		lowerLegR = rbWorld->addRigidBody(state,body,collidable);
	}

	// UpperArmR
	{
		PfxCapsule capsule(0.25f,0.15f);
		PfxShape shape;
		shape.reset();
		shape.setOffsetOrientation(PfxQuat(0.0f,0.0f,0.70711f,0.70711f));
		shape.setCapsule(capsule);
		collidable.reset();
		collidable.addShape(shape);
		collidable.finish();
		body.reset();
		body.setMass(5.0f);
		body.setInertia(inertiaScale * pfxCalcInertiaCylinderY(0.25f+0.15f,0.15f,5.0f));
		state.reset();
		state.setPosition(offsetPosition + rotate(offsetOrientation,PfxVector3(-0.72813f,2.87483f,0.0f)));
		state.setOrientation(offsetOrientation * PfxQuat(0.0f,0.0f,-0.70711f,0.70711f));
		state.setMotionType(kPfxMotionTypeActive);
		state.setUseSleep(1);
		upperArmR = rbWorld->addRigidBody(state,body,collidable);
	}

	// LowerArmR
	{
		PfxCapsule capsule(0.225f,0.15f);
		PfxShape shape;
		shape.reset();
		shape.setOffsetOrientation(PfxQuat(0.0f,0.0f,0.70711f,0.70711f));
		shape.setCapsule(capsule);
		collidable.reset();
		collidable.addShape(shape);
		collidable.finish();
		body.reset();
		body.setMass(3.0f);
		body.setInertia(inertiaScale * pfxCalcInertiaCylinderY(0.225f+0.15f,0.15f,3.0f));
		state.reset();
		state.setPosition(offsetPosition + rotate(offsetOrientation,PfxVector3(-1.42931f,2.87483f,0.0f)));
		state.setOrientation(offsetOrientation * PfxQuat(0.0f,0.0f,-0.70711f,0.70711f));
		state.setMotionType(kPfxMotionTypeActive);
		state.setUseSleep(1);
		lowerArmR = rbWorld->addRigidBody(state,body,collidable);
	}

	PfxUInt32 numRagdollJoints = 0;
	PfxUInt32 ragdollJointIds[20];

	// Joint Torso-Chest
	{
		PfxRigidState &stateA = rbWorld->getRigidState(torso);
		PfxRigidState &stateB = rbWorld->getRigidState(chest);

		PfxSwingTwistJointInitParam jparam;
		jparam.anchorPoint = offsetPosition + rotate(offsetOrientation,PfxVector3(0.0f,2.26425f,0.0f));
		jparam.twistAxis = rotate(offsetOrientation,PfxVector3(0.0f,1.0f,0.0f));
		
		PfxJoint joint;
		pfxInitializeSwingTwistJoint(joint,stateA,stateB,jparam);
		ragdollJointIds[numRagdollJoints++] = rbWorld->addJoint(joint);
		rbWorld->appendNonContactPair(torso,chest);
	}
	
	// Joint Chest-Head
	{
		PfxRigidState &stateA = rbWorld->getRigidState(chest);
		PfxRigidState &stateB = rbWorld->getRigidState(head);

		PfxSwingTwistJointInitParam jparam;
		jparam.anchorPoint = offsetPosition + rotate(offsetOrientation,PfxVector3(0.0f,3.13575f,0.0f));
		jparam.twistAxis = rotate(offsetOrientation,PfxVector3(0.0f,1.0f,0.0f));

		PfxJoint joint;
		pfxInitializeSwingTwistJoint(joint,stateA,stateB,jparam);
		ragdollJointIds[numRagdollJoints++] = rbWorld->addJoint(joint);
		rbWorld->appendNonContactPair(chest,head);
	}

	// Joint Chest-UpperArmL
	{
		PfxRigidState &stateA = rbWorld->getRigidState(chest);
		PfxRigidState &stateB = rbWorld->getRigidState(upperArmL);

		PfxSwingTwistJointInitParam jparam;
		jparam.anchorPoint = offsetPosition + rotate(offsetOrientation,PfxVector3(0.40038f,2.87192f,0.0f));
		jparam.twistAxis = rotate(offsetOrientation,PfxVector3(1.0f,0.0f,0.0f));
		jparam.swingLowerAngle = 0.0f;
		jparam.swingUpperAngle = 1.57f;

		PfxJoint joint;
		pfxInitializeSwingTwistJoint(joint,stateA,stateB,jparam);
		ragdollJointIds[numRagdollJoints++] = rbWorld->addJoint(joint);
		rbWorld->appendNonContactPair(chest,upperArmL);
	}

	// Joint UpperArmL-LowerArmL
	{
		PfxRigidState &stateA = rbWorld->getRigidState(upperArmL);
		PfxRigidState &stateB = rbWorld->getRigidState(lowerArmL);

		PfxHingeJointInitParam jparam;
		jparam.anchorPoint = offsetPosition + rotate(offsetOrientation,PfxVector3(1.08651f,2.87483f,0.00000f));
		jparam.axis = rotate(offsetOrientation,PfxVector3(0.0f,-1.0f,0.0f));
		jparam.lowerAngle = 0.0f;
		jparam.upperAngle = 1.57f;

		PfxJoint joint;
		pfxInitializeHingeJoint(joint,stateA,stateB,jparam);
		ragdollJointIds[numRagdollJoints++] = rbWorld->addJoint(joint);
		rbWorld->appendNonContactPair(upperArmL,lowerArmL);
	}

	// Joint Chest-UpperArmR
	{
		PfxRigidState &stateA = rbWorld->getRigidState(chest);
		PfxRigidState &stateB = rbWorld->getRigidState(upperArmR);

		PfxSwingTwistJointInitParam jparam;
		jparam.anchorPoint = offsetPosition + rotate(offsetOrientation,PfxVector3(-0.40360f,2.87499f,0.00000f));
		jparam.twistAxis = rotate(offsetOrientation,PfxVector3(-1.0f,0.0f,0.0f));
		jparam.swingLowerAngle = 0.0f;
		jparam.swingUpperAngle = 1.57f;

		PfxJoint joint;
		pfxInitializeSwingTwistJoint(joint,stateA,stateB,jparam);
		ragdollJointIds[numRagdollJoints++] = rbWorld->addJoint(joint);
		rbWorld->appendNonContactPair(chest,upperArmR);
	}

	// Joint UpperArmR-LowerArmR
	{
		PfxRigidState &stateA = rbWorld->getRigidState(upperArmR);
		PfxRigidState &stateB = rbWorld->getRigidState(lowerArmR);

		PfxHingeJointInitParam jparam;
		jparam.anchorPoint = offsetPosition + rotate(offsetOrientation,PfxVector3(-1.09407f,2.87483f,0.00000f));
		jparam.axis = rotate(offsetOrientation,PfxVector3(0.0f,-1.0f,0.0f));
		jparam.lowerAngle = 0.0f;
		jparam.upperAngle = 1.57f;

		PfxJoint joint;
		pfxInitializeHingeJoint(joint,stateA,stateB,jparam);
		ragdollJointIds[numRagdollJoints++] = rbWorld->addJoint(joint);
		rbWorld->appendNonContactPair(upperArmR,lowerArmR);
	}

	// Joint Torso-UpperLegL
	{
		PfxRigidState &stateA = rbWorld->getRigidState(torso);
		PfxRigidState &stateB = rbWorld->getRigidState(upperLegL);

		PfxUniversalJointInitParam jparam;
		jparam.anchorPoint = offsetPosition + rotate(offsetOrientation,PfxVector3(0.20993f,1.69661f,0.00000f));
		jparam.axis = rotate(offsetOrientation,PfxVector3(0.0f,-1.0f,0.0f));
		jparam.swing1LowerAngle = 0.0f;
		jparam.swing1UpperAngle = 0.52f;
		jparam.swing2LowerAngle = 0.0f;
		jparam.swing2UpperAngle = 1.57f;

		PfxJoint joint;
		pfxInitializeUniversalJoint(joint,stateA,stateB,jparam);
		ragdollJointIds[numRagdollJoints++] = rbWorld->addJoint(joint);
		rbWorld->appendNonContactPair(torso,upperLegL);
	}

	// Joint Torso-UpperLegR
	{
		PfxRigidState &stateA = rbWorld->getRigidState(torso);
		PfxRigidState &stateB = rbWorld->getRigidState(upperLegR);

		PfxUniversalJointInitParam jparam;
		jparam.anchorPoint = offsetPosition + rotate(offsetOrientation,PfxVector3(-0.21311f,1.69661f,0.00000f));
		jparam.axis = rotate(offsetOrientation,PfxVector3(0.0f,-1.0f,0.0f));
		jparam.swing1LowerAngle = 0.0f;
		jparam.swing1UpperAngle = 0.52f;
		jparam.swing2LowerAngle = 0.0f;
		jparam.swing2UpperAngle = 1.57f;

		PfxJoint joint;
		pfxInitializeUniversalJoint(joint,stateA,stateB,jparam);
		ragdollJointIds[numRagdollJoints++] = rbWorld->addJoint(joint);
		rbWorld->appendNonContactPair(torso,upperLegR);
	}

	// Joint UpperLegL-LowerLegL
	{
		PfxRigidState &stateA = rbWorld->getRigidState(upperLegL);
		PfxRigidState &stateB = rbWorld->getRigidState(lowerLegL);

		PfxHingeJointInitParam jparam;
		jparam.anchorPoint = offsetPosition + rotate(offsetOrientation,PfxVector3(0.21000f,0.97062f,0.00000f));
		jparam.axis = rotate(offsetOrientation,PfxVector3(1.0f,0.0f,0.0f));
		jparam.lowerAngle = 0.0f;
		jparam.upperAngle = 1.57f;

		PfxJoint joint;
		pfxInitializeHingeJoint(joint,stateA,stateB,jparam);
		ragdollJointIds[numRagdollJoints++] = rbWorld->addJoint(joint);
		rbWorld->appendNonContactPair(upperLegL,lowerLegL);
	}

	// Joint UpperLegR-LowerLegR
	{
		PfxRigidState &stateA = rbWorld->getRigidState(upperLegR);
		PfxRigidState &stateB = rbWorld->getRigidState(lowerLegR);

		PfxHingeJointInitParam jparam;
		jparam.anchorPoint = offsetPosition + rotate(offsetOrientation,PfxVector3(-0.21000f,0.97062f,0.00000f));
		jparam.axis = rotate(offsetOrientation,PfxVector3(1.0f,0.0f,0.0f));
		jparam.lowerAngle = 0.0f;
		jparam.upperAngle = 1.57f;

		PfxJoint joint;
		pfxInitializeHingeJoint(joint,stateA,stateB,jparam);
		ragdollJointIds[numRagdollJoints++] = rbWorld->addJoint(joint);
		rbWorld->appendNonContactPair(upperLegR,lowerLegR);
	}

	// Add angular damping to ragdoll joints
	for(PfxUInt32 i=0;i<numRagdollJoints;i++) {
		PfxJoint &joint = rbWorld->getJoint(ragdollJointIds[i]);
		joint.m_constraints[0].m_warmStarting = 1;
		joint.m_constraints[1].m_warmStarting = 1;
		joint.m_constraints[2].m_warmStarting = 1;
		joint.m_constraints[3].m_damping = 0.05f;
		joint.m_constraints[4].m_damping = 0.05f;
		joint.m_constraints[5].m_damping = 0.05f;
	}
}

void createSceneRagdolls()
{
	float stairHeight = 0.5f;
	for(int i=0;i<5;i++) {
		int stair = createBrick(
			PfxVector3(0.0f,stairHeight * ((float)i + 0.5f), - i * 0.5f),
			PfxQuat::identity(),
			PfxVector3(10.0f,0.25f,2.5f - i * 0.5f),
			1.0f);
		rbWorld->getRigidState(stair).setMotionType(kPfxMotionTypeFixed);
	}
	
	PfxVector3 pos[5] = {
		PfxVector3(-6.0f,3.0f,0.0f),
		PfxVector3(-3.0f,3.5f,0.0f),
		PfxVector3( 0.0f,3.0f,0.0f),
		PfxVector3( 3.0f,3.5f,0.0f),
		PfxVector3( 6.0f,3.0f,0.0f),
	};

	PfxQuat ori[5] = {
		PfxQuat::rotationX(-0.3f),
		PfxQuat::rotationX(-0.1f),
		PfxQuat::rotationX( 0.2f),
		PfxQuat::rotationX(-0.2f),
		PfxQuat::rotationX( 0.4f),
	};
	
	createSceneRagdoll(pos[0],ori[0]);
	createSceneRagdoll(pos[1],ori[1]);
	createSceneRagdoll(pos[2],ori[2]);
	createSceneRagdoll(pos[3],ori[3]);
	createSceneRagdoll(pos[4],ori[4]);
}

void createRayCastObject()
{
	PfxRigidState state;
	PfxRigidBody body;
	PfxCollidable collidable;

	// cylinder
	{
		PfxCylinder cylinder(4.0f,2.9f);
		PfxShape shape;
		shape.reset();
		shape.setCylinder(cylinder);
		shape.setOffsetOrientation(PfxQuat::rotationZ(SCE_PFX_PI*0.5f));
		collidable.reset();
		collidable.addShape(shape);
		collidable.finish();
		body.reset();
		body.setMass(3.0f);
		body.setInertia(pfxCalcInertiaCylinderY(12.0f,6.0f,2.0f));
		state.reset();
		state.setPosition(PfxVector3(0.0f,18.0f,0.0f));
		state.setMotionType(kPfxMotionTypeActive);
		state.setUseSleep(1);

		raycastObjId = rbWorld->addRigidBody(state,body,collidable);
	}
	
	numRays = NUM_RAYS;
}

void updateRayCastObject()
{
	if(raycastObjId < 0) return;
	
	// Setup ray inputs
	PfxVector3 direction(1.0f,0.0f,0.0f);
	PfxQuat rotY = PfxQuat::rotationY(2.0f*SCE_PFX_PI/(float)NUM_RAYS);

	PfxRigidState &state = rbWorld->getRigidState(raycastObjId);

	for(int i=0;i<numRays;i++) {
		rayInputs[i].reset();
		rayInputs[i].m_startPosition = state.getPosition() + rotate(state.getOrientation(),3.0f*direction);
		rayInputs[i].m_direction = rotate(state.getOrientation(),5.0f * direction);
		rayOutputs[i].m_contactFlag = false;

		direction = rotate(rotY,direction);
	}

	// Setup casting area
	areaCenter = state.getPosition();
	areaExtent = PfxVector3(8.1f);
}

void castRayCastObject()
{
	rbWorld->setCastArea(areaCenter,areaExtent);
	rbWorld->castRays(rayInputs,rayOutputs,NUM_RAYS);
}

void physicsCreateScene(int sceneId)
{
	const int numScenes = 5;
	sSceneId = sceneId % numScenes;

	physicsResetWorld();

	switch(sSceneId) {
		case 0: // simple primitives
		createSceneBoxGround();
		createScenePrimitives();
		break;

		case 1: // stacking
		createSceneBoxGround();
		createSceneStacking();
		break;
		
		case 2: // ragdolls
		createSceneBoxGround();
		createSceneRagdolls();
		break;
		
		case 3: // large mesh
		createSceneLandscape(PfxVector3(-10.0f));
		createSceneFallingPrimitives();
		break;

		case 4: // ray casting
		//createSceneBoxGround();
		createSceneLandscape(PfxVector3(-10.0f));
		createSceneFallingPrimitives();
		createRayCastObject();
		updateRayCastObject();
		break;
	}

	int n = rbWorld->getRigidBodyCount();
	int j = rbWorld->getJointCount();

	SCE_PFX_PRINTF("PfxRigidBodyWorld %5d bytes\n",sizeof(PfxRigidBodyWorld));

	SCE_PFX_PRINTF("----- Size of rigid body buffer ------\n");
	SCE_PFX_PRINTF("                  size * num = total\n");
	SCE_PFX_PRINTF("PfxRigidState      %5d * %5d = %5d bytes\n",sizeof(PfxRigidState),n,sizeof(PfxRigidState)*n);
	SCE_PFX_PRINTF("PfxRigidBody       %5d * %5d = %5d bytes\n",sizeof(PfxRigidBody),n,sizeof(PfxRigidBody)*n);
	SCE_PFX_PRINTF("PfxCollidable      %5d * %5d = %5d bytes\n",sizeof(PfxCollidable),n,sizeof(PfxCollidable)*n);
	SCE_PFX_PRINTF("PfxJoint           %5d * %5d = %5d bytes\n",sizeof(PfxJoint),j,sizeof(PfxJoint)*j);
	SCE_PFX_PRINTF("PfxSolverBody      %5d * %5d = %5d bytes\n",sizeof(PfxSolverBody),n,sizeof(PfxSolverBody)*n);
	SCE_PFX_PRINTF("PfxBroadphaseProxy %5d * %5d = %5d bytes\n",sizeof(PfxBroadphaseProxy),n,sizeof(PfxBroadphaseProxy)*n);
	SCE_PFX_PRINTF("PfxContactManifold %5d * %5d = %5d bytes\n",sizeof(PfxContactManifold),rbWorld->getContactCapacity(),sizeof(PfxContactManifold)*rbWorld->getContactCapacity());
	SCE_PFX_PRINTF("PfxBroadphasePair  %5d * %5d = %5d bytes\n",sizeof(PfxBroadphasePair),rbWorld->getContactCapacity(),sizeof(PfxBroadphasePair)*rbWorld->getContactCapacity());

	int totalBytes = 
		(sizeof(PfxRigidState) + sizeof(PfxRigidBody) + sizeof(PfxCollidable) + sizeof(PfxSolverBody) + sizeof(PfxBroadphaseProxy)) * n +
		(sizeof(PfxContactManifold) + sizeof(PfxBroadphasePair)) * rbWorld->getContactCapacity();
	SCE_PFX_PRINTF("----------------------------------------------------------\n");
	SCE_PFX_PRINTF("Total %5d bytes\n",totalBytes);

#ifdef ENABLE_DEBUG_DRAW
	g_debugRender->resetVisible(world->getRigidBodyCapacity());
#endif
}

///////////////////////////////////////////////////////////////////////////////
// Initialize / Finalize Engine

bool physicsInit(const PfxVector3& worldSize)
{
	largeMeshes	= new PfxArray<PfxLargeTriMesh*>();
	convexMeshes = new PfxArray<PfxConvexMesh*>();
	renderMeshes = new PfxMap<void*,int>(largeMeshes->capacity()+convexMeshes->capacity());
	
	PfxRigidBodyWorldParam worldParam;

	worldParam.simulationFlag = SCE_PFX_ENABLE_SLEEP;

	worldParam.worldCenter = PfxVector3(0.0f);
	//worldParam.worldExtent = PfxVector3(250.0f, 100.0f, 250.0f);
	worldParam.worldExtent = worldSize;

	//J ワールドパラメータに記述されたシーンの規模からバイトサイズを計算し、メモリを確保します。
	//E Calculate byte size from a scene scale described in a world parameter and allocate memory for pool buffer.
	poolBytes = PfxRigidBodyWorld::getRigidBodyWorldBytes(worldParam);
	poolBuff = new unsigned char [poolBytes];

	SCE_PFX_PRINTF("pool %d bytes\n",poolBytes);

	worldParam.poolBytes = poolBytes;
	worldParam.poolBuff = poolBuff;

	//J PfxRigidBodyWorldクラスのインスタンスを作成し、ワールドを初期化します。
	//E Create an instance of PfxRigidBodyWorld and initialize a world
	rbWorld = new PfxRigidBodyWorld(worldParam);

	rbWorld->initialize();

	return true;
}

void physicsReleaseMeshes()
{
	for (PfxUInt32 c=0; c<largeMeshes->size(); ++c)
	{
		pfxReleaseLargeTriMesh(*(*largeMeshes)[c]);
		SCE_PFX_UTIL_FREE((*largeMeshes)[c]);
	}
	largeMeshes->clear();

	for (PfxUInt32 c=0; c<convexMeshes->size(); ++c)
	{
		pfxReleaseConvexMesh(*(*convexMeshes)[c]);
		SCE_PFX_UTIL_FREE((*convexMeshes)[c]);
	}
	convexMeshes->clear();
	
	renderMeshes->clear();
}

void physicsResetWorld()
{
	physicsReleaseMeshes();

	if(rbWorld) {
		rbWorld->reset();
	}

	numRays = 0;
	raycastObjId = -1;
	pickJointId = -1;
}

void physicsRelease()
{
	rbWorld->finalize();

	physicsResetWorld();

	delete rbWorld;
	delete [] poolBuff;

	delete renderMeshes;
	delete largeMeshes;
	delete convexMeshes;
}

void physicsSimulate()
{
	rbWorld->simulate();

#if 0
	if(sSceneId==4) {
		updateRayCastObject();
		castRayCastObject();
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
// Picking

inline PfxVector3 calcLocalCoord(const PfxRigidState &state,const PfxVector3 &coord)
{
	return rotate(conj(state.getOrientation()),(coord - state.getPosition()));
}

//J	ピックモード
//J	0 : ピックした剛体を動かす 
//J	1 : 剛体を投げる
//J	2 : ピックした剛体を消去
//E	Pick mode
//E	0 : Move picked rigid body
//E	1 : Throw rigid body
//E	2 : Remove picked rigid body
#define PICK_MODE 0 

#if (PICK_MODE == 0)

PfxVector3 physicsPickStart(const PfxVector3 &p1,const PfxVector3 &p2)
{
	PfxRayInput pickRay;
	PfxRayOutput pickOut;
	
	pickRay.m_contactFilterSelf = pickRay.m_contactFilterTarget = 0xffffffff;
	pickRay.m_startPosition = p1;
	pickRay.m_direction = p2-p1;
	pickRay.m_facetMode = SCE_PFX_RAY_FACET_MODE_FRONT_ONLY;
	
	rbWorld->castSingleRay(pickRay,pickOut);
	
	if(pickOut.m_contactFlag) {
		PfxBallJointInitParam jparam;
		jparam.anchorPoint = pickOut.m_contactPoint;

		PfxRigidState &stateA = rbWorld->getRigidState(0);
		PfxRigidState &stateB = rbWorld->getRigidState(pickOut.m_objectId);

		if(pickJointId < 0) {
			PfxJoint joint;
			pfxInitializeBallJoint(joint,stateA,stateB,jparam);
			pickJointId = rbWorld->addJoint(joint);
		}

		PfxJoint &pickJoint = rbWorld->getJoint(pickJointId);

		pfxInitializeBallJoint(pickJoint,stateA,stateB,jparam);
		rbWorld->updateJoint(pickJointId);

		PfxRigidBody &bodyB = rbWorld->getRigidBody(pickOut.m_objectId);

		pickJoint.m_constraints[0].m_maxImpulse = bodyB.getMass() * 2.0f;
		pickJoint.m_constraints[1].m_maxImpulse = bodyB.getMass() * 2.0f;
		pickJoint.m_constraints[2].m_maxImpulse = bodyB.getMass() * 2.0f;

		SCE_PFX_PRINTF("pick objId %d ",pickOut.m_objectId);
		if(pickOut.m_subData.m_type == PfxSubData::MESH_INFO) {
			SCE_PFX_PRINTF("mesh islandId %d facetId %d",pickOut.m_subData.getIslandId(),pickOut.m_subData.getFacetId());
		}
		SCE_PFX_PRINTF("\n");

		return pickOut.m_contactPoint;
	}

	return PfxVector3(0.0f);
}

void physicsPickUpdate(const PfxVector3 &p)
{
	if(pickJointId < 0) return;

	PfxJoint &pickJoint = rbWorld->getJoint(pickJointId);

	if(pickJoint.m_active>0) {
		PfxRigidState &stateA = rbWorld->getRigidState(pickJoint.m_rigidBodyIdA);
		PfxRigidState &stateB = rbWorld->getRigidState(pickJoint.m_rigidBodyIdB);
		pickJoint.m_anchorA = calcLocalCoord(stateA,p);
		if(stateB.isAsleep()) {
			stateB.wakeup();
		}
	}
}

void physicsPickEnd()
{
	if(pickJointId < 0) return;

	PfxJoint &pickJoint = rbWorld->getJoint(pickJointId);
	
	if(pickJoint.m_active>0) {
		pickJoint.m_active = 0;
	}
}

#elif (PICK_MODE == 1)

PfxVector3 physicsPickStart(const PfxVector3 &p1,const PfxVector3 &p2)
{
	PfxVector3 position = p1;
	PfxVector3 velocity = 50.0f * normalize(p2-p1);
	PfxRigidState state;
	PfxRigidBody body;
	PfxCollidable collidable;

	int type = rand()%4;

	// sphere
	if(type == 0) {
		PfxSphere sphere(0.5f);
		PfxShape shape;
		shape.reset();
		shape.setSphere(sphere);
		collidable.reset();
		collidable.addShape(shape);
		collidable.finish();
		body.reset();
		body.setMass(1.0f);
		body.setInertia(pfxCalcInertiaSphere(0.5f,1.0f));
		state.reset();
		state.setPosition(position);
		state.setLinearVelocity(velocity);
		state.setMotionType(kPfxMotionTypeActive);
		state.setUseSleep(1);

		world->addRigidBody(state,body,collidable);
	}

	// box
	else if(type == 1) {
		PfxBox box(0.5f,0.5f,0.5f);
		PfxShape shape;
		shape.reset();
		shape.setBox(box);
		collidable.reset();
		collidable.addShape(shape);
		collidable.finish();
		body.reset();
		body.setMass(1.0f);
		body.setInertia(pfxCalcInertiaBox(PfxVector3(0.5f),1.0f));
		state.reset();
		state.setPosition(position);
		state.setLinearVelocity(velocity);
		state.setMotionType(kPfxMotionTypeActive);
		state.setUseSleep(1);

		world->addRigidBody(state,body,collidable);
	}

	// capsule
	else if(type == 2) {
		PfxCapsule capsule(0.5f,0.25f);
		PfxShape shape;
		shape.reset();
		shape.setCapsule(capsule);
		collidable.reset();
		collidable.addShape(shape);
		collidable.finish();
		body.reset();
		body.setMass(1.0f);
		body.setInertia(pfxCalcInertiaCylinderX(1.0f,0.5f,1.0f));
		state.reset();
		state.setPosition(position);
		state.setLinearVelocity(velocity);
		state.setMotionType(kPfxMotionTypeActive);
		state.setUseSleep(1);

		world->addRigidBody(state,body,collidable);
	}

	// cylinder
	else if(type == 3) {
		PfxCylinder cylinder(0.5f,0.25f);
		PfxShape shape;
		shape.reset();
		shape.setCylinder(cylinder);
		collidable.reset();
		collidable.addShape(shape);
		collidable.finish();
		body.reset();
		body.setMass(1.0f);
		body.setInertia(pfxCalcInertiaCylinderX(1.0f,0.5f,1.0f));
		state.reset();
		state.setPosition(position);
		state.setLinearVelocity(velocity);
		state.setMotionType(kPfxMotionTypeActive);
		state.setUseSleep(1);

		world->addRigidBody(state,body,collidable);
	}

	return PfxVector3(0.0f);
}

void physicsPickUpdate(const PfxVector3 &p)
{
}

void physicsPickEnd()
{
}

#elif (PICK_MODE == 2)

PfxVector3 physicsPickStart(const PfxVector3 &p1,const PfxVector3 &p2)
{
	PfxRayInput pickRay;
	PfxRayOutput pickOut;
	
	pickRay.m_contactFilterSelf = pickRay.m_contactFilterTarget = 0xffffffff;
	pickRay.m_startPosition = p1;
	pickRay.m_direction = p2-p1;
	pickRay.m_facetMode = SCE_PFX_RAY_FACET_MODE_FRONT_ONLY;
	
	world->castSingleRay(pickRay,pickOut);
	
	if(pickOut.m_contactFlag && !world->isRemovedRigidBody(pickOut.m_objectId)) {
		world->removeRigidBody(pickOut.m_objectId);
	}

	return PfxVector3(0.0f);
}

void physicsPickUpdate(const PfxVector3 &p)
{
}

void physicsPickEnd()
{
}

#endif

///////////////////////////////////////////////////////////////////////////////
// Get Information

int physicsGetNumRigidbodies()
{
	return rbWorld->getRigidBodyCount();
}

const PfxRigidState& physicsGetState(int id)
{
	return rbWorld->getRigidState(id);
}

const PfxRigidBody& physicsGetBody(int id)
{
	return rbWorld->getRigidBody(id);
}

const PfxCollidable& physicsGetCollidable(int id)
{
	return rbWorld->getCollidable(id);
}

int physicsGetNumContacts()
{
	return rbWorld->getContactCount();
}

const PfxContactManifold &physicsGetContact(int id)
{
	return rbWorld->getContactManifold(id);
}

const PfxIsland* physicsGetIslands()
{
	return rbWorld->getIsland();
}

int physicsGetNumRays()
{
	return numRays;
}

const PfxRayInput& physicsGetRayInput(int id)
{
	return rayInputs[id];
}

const PfxRayOutput& physicsGetRayOutput(int id)
{
	return rayOutputs[id];
}

int physicsGetRenderMeshId(void *collisionMesh)
{
	int meshId = -1;
	renderMeshes->find(collisionMesh,meshId);
	return meshId;
}

// 以下Dx追加関数
PfxRigidBodyWorld& physicsGetWorld()
{
	return *rbWorld;
}
