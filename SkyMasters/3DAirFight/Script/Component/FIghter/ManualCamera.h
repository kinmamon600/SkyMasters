#ifndef _MANUALCAMERA_H
#define _MANUALCAMERA_H

// ライブラリ・ヘッダ
#include "../Component.h"
#include "../ComponentUpdateOrder.h"

// 前方宣言
class Transform;
class PhysicsColliderSphere;

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
	void SetCamera(const Transform* p_player_tr, PhysicsColliderSphere* p_player_pc, float x_value, float y_value, float fov);

private:
	float cameraFixationOffset = 550.0f;
	float cameraDefaultPitchAngle = 3.0f;
	float cameraDistance = 855.0f;

	float cameraCenterAreaX = 20.0f;
	float cameraCenterAreaY = 10.0f;

	float cameraYawAngle = 8.75f;
	float cameraPitchAngle = 5.5f;

	float cameraTurnDistanceX = 94.0f;
	float cameraTurnDistanceY = 85.0f;
};

#endif