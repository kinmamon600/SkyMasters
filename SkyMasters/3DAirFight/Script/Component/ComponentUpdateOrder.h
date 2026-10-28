#ifndef _COMPONENTUPDATEORDER_H
#define _COMPONENTUPDATEORDER_H

// 各コンポーネントの更新順序
// 上にある(番号が若い)程先に更新される
enum class ComponentUpdateOrder
{
	// 更新処理
	Input,
	PhysicsCollider,
	Transform,
	Behaviour,

	// 描画処理
	Camera,
	SkyboxRenderer,
	ModelRenderer,
	UIRenderer,
};

#endif