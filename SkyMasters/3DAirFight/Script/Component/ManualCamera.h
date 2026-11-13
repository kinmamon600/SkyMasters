#pragma once

#include <cmath>
#include "DxLib.h"

#include "Camera.h"
#include"Component.h"
#include"ComponentManager.h"
#include"Transform.h"
#include"PhysicsCollider.h"

class ManualCamera :public Component
{
public:
	ManualCamera(Actor* owner)
		:Component(owner, static_cast<int>(ComponentUpdateOrder::Behaviour)) {};

	~ManualCamera(){}

	void SetCamera(const Transform* p_player_tr,  PhysicsCollider* p_player_pc, float x_value, float y_value, float fov);

private:
	float cameraFixationOffset;
	float cameraDefaultPitchAngle;
	float cameraDistance;

	float cameraCenterAreaX;
	float cameraCenterAreaY;

	float cameraYawAngle;
	float cameraPitchAngle;

	float cameraTurnDistanceX;
	float cameraTurnDistanceY;
};
