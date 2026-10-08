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
Physics Effects under the filename: physics_effects_li/*
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

#ifndef _SCE_PFX_RAY_CAST_H
#define _SCE_PFX_RAY_CAST_H

#include "../../base_level/rigidbody/pfx_rigid_state.h"
#include "../../base_level/collision/pfx_collidable.h"
#include "../../base_level/collision/pfx_ray.h"
#include "../../base_level/broadphase/pfx_broadphase_proxy.h"

///////////////////////////////////////////////////////////////////////////////
// RayCast
//物理エンジン内でどう処理するかに必要な情報の定義

namespace sce {
	namespace PhysicsEffects {

		//PfxBroadphaseProxyとはブロードフェーズで物体を管理するためのデータ

		//RayCastを物理演算で使用するための情報たち
		struct PfxRayCastParam {
			PfxRigidState* offsetRigidStates;	//剛体状態データへのポインタ
			PfxCollidable* offsetCollidables;	//剛体の衝突形状へのポインタ
			PfxBroadphaseProxy* proxiesX;		//ブロードフェーズでX軸方向に検索する
			PfxBroadphaseProxy* proxiesY;		//ブロードフェーズでY軸方向に検索する
			PfxBroadphaseProxy* proxiesZ;		//ブロードフェーズでZ軸方向に検索する
			PfxBroadphaseProxy* proxiesXb;		//ブロードフェーズで-X軸方向に検索する
			PfxBroadphaseProxy* proxiesYb;		//ブロードフェーズで-Y軸方向に検索する
			PfxBroadphaseProxy* proxiesZb;		//ブロードフェーズで-Z軸方向に検索する
			PfxUInt32 numProxies;				//プロキシの数
			SCE_PFX_PADDING(1, 12)
				PfxVector3 rangeCenter;				//ブロードフェーズで調べる範囲の中心
			PfxVector3 rangeExtent;				//ブロードフェーズで調べる範囲の大きさ
		};

		void pfxCastSingleRay(const PfxRayInput& rayInput, PfxRayOutput& rayOutput, const PfxRayCastParam& param);

	} //namespace PhysicsEffects
} //namespace sce
#endif // _SCE_PFX_RAY_CAST_H
cense.txt
*/

#ifndef _SCE_PFX_RAY_CAST_H
#define _SCE_PFX_RAY_CAST_H

#include "../../base_level/rigidbody/pfx_rigid_state.h"
#include "../../base_level/collision/pfx_collidable.h"
#include "../../base_level/collision/pfx_ray.h"
#include "../../base_level/broadphase/pfx_broadphase_proxy.h"

///////////////////////////////////////////////////////////////////////////////
// RayCast

namespace sce {
namespace PhysicsEffects {

struct PfxRayCastParam {
	PfxRigidState *offsetRigidStates;
	PfxCollidable *offsetCollidables;
	PfxBroadphaseProxy *proxiesX;
	PfxBroadphaseProxy *proxiesY;
	PfxBroadphaseProxy *proxiesZ;
	PfxBroadphaseProxy *proxiesXb;
	PfxBroadphaseProxy *proxiesYb;
	PfxBroadphaseProxy *proxiesZb;
	PfxUInt32 numProxies;
	SCE_PFX_PADDING(1,12)
	PfxVector3 rangeCenter;
	PfxVector3 rangeExtent;
};

void pfxCastSingleRay(const PfxRayInput &rayInput,PfxRayOutput &rayOutput,const PfxRayCastParam &param);

} //namespace PhysicsEffects
} //namespace sce
#endif // _SCE_PFX_RAY_CAST_H
