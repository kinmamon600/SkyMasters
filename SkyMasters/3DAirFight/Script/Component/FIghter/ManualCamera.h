#ifndef _MANUALCAMERA_H
#define _MANUALCAMERA_H

// ライブラリ・ヘッダ
#include "../Component.h"
#include "../ComponentUpdateOrder.h"

// 前方宣言
class Fighter;
class Transform;
class PhysicsCollider;

class ManualCamera : public Component
{
public:
	// コンストラクタ
	ManualCamera(Actor* owner)
		: Component(owner, static_cast<int>(ComponentUpdateOrder::Behaviour)) {
	}

	// デストラクタ
	~ManualCamera() {}

	// カメラコンポーネントを設定
	void SetCamera(const Fighter* p_player_fighter, const Transform* p_player_tr, PhysicsCollider* p_player_pc, float x_value, float y_value, float fov);

private:
	
};

#endif