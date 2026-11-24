#ifndef _COMPONENTUPDATEORDER_H
#define _COMPONENTUPDATEORDER_H

// 各コンポーネントの更新順序
// 上にある(番号が若い)程先に更新される
enum class ComponentUpdateOrder
{
	// 更新処理
	PhysicsCollider,
	Input,
	Transform,
	Behaviour,
	Sound,

	// 描画処理
	Camera,

	StartRenderComponent,	// ここからレンダリング系コンポーネント (この値はオーダーに設定しない)
	SkyboxRenderer,
	BackgroundRenderer,
	ModelRenderer,
	EndRenderComponent,		// ここまでレンダリング系コンポーネント (この値はオーダーに設定しない)

	UIRenderer,
};

#endif