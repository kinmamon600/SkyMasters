// ライブラリ・ヘッダ
#include <cmath>

#include "Manual.h"
#include "../../Screen/Screen.h"
#include "../../Actor/Actor.h"
#include "../Input.h"
#include "../../Input/ControllerInput.h"
#include "../PhysicsColliderSphere.h"


void Manual::FighterControl()
{
	// 入力・物理コライダーの取得
	Input* input = m_owner->GetComponent<Input>();
	PhysicsColliderSphere* pcs = m_owner->GetComponent<PhysicsColliderSphere>();

	// 自機の座標・向きの取得
	VECTOR forward = pcs->GetDirection(VGet(0.0f, 0.0f, -1.0f));

	// 速度設定
	// hpが0なら0
	VECTOR linear_velocity = VScale(forward, speed);
<<<<<<< HEAD
=======
	//VECTOR linear_velocity = VGet(0, 0, -speed);
>>>>>>> keigo

	// 角速度設定 & ヨー時の傾き設定
	// プレイヤー操作時で無ければ0
	float pitch = 0.0f;
	float yaw = 0.0f;
	
	float current_yawslopeangle = 0.0f;
	float target_yawslopeangle = 0.0f;
	
	// ピッチの角速度設定
	float pitch_dot = VDot(VGet(0.0f, 1.0f, 0.0f), forward);
	float pitch_target = (1.0f - std::abs(pitch_dot)) * (pitchAngleMax / 90.0f) * (float)(input->GetAnalog(Input::LY)) / ANALOG_INPUT_MAX;
	pitch = (pitch_dot - pitch_target) * (90.0f / pitchAngleMax) * pitchAngularVelocity;

	// ヨーの角速度設定
	yaw = -(float)(input->GetAnalog(Input::LX)) / ANALOG_INPUT_MAX * yawAngularVelocity;
	
	// ヨーの傾き設定
	target_yawslopeangle = -(float)(input->GetAnalog(Input::LX)) / ANALOG_INPUT_MAX * yawSlopeAngleMax;
	
	if (target_yawslopeangle > yawSlopeAngle)
	{
		float spd = VariableTransition_QuadraticFluctuation((target_yawslopeangle - yawSlopeAngle) / (yawSlopeAngleMax * 2.0f),
			yawSlopeAngleSpeedMin, yawSlopeAngleSpeedMax);
		current_yawslopeangle = yawSlopeAngle + spd / Screen::FPS;
		if (current_yawslopeangle > target_yawslopeangle) { current_yawslopeangle = target_yawslopeangle; }
	}
	else if (target_yawslopeangle < yawSlopeAngle)
	{
		float spd = VariableTransition_QuadraticFluctuation((yawSlopeAngle - target_yawslopeangle) / (yawSlopeAngleMax * 2.0f),
			yawSlopeAngleSpeedMin, yawSlopeAngleSpeedMax);
		current_yawslopeangle = yawSlopeAngle - spd / Screen::FPS;
		if (current_yawslopeangle < target_yawslopeangle) { current_yawslopeangle = target_yawslopeangle; }
	}
	else
	{
		current_yawslopeangle = target_yawslopeangle;
	}
	
	// 機体の軸方向設定
	VECTOR axis_z = VScale(forward, -1.0f);
	VECTOR direction = pcs->GetDirection(VGet(1.0f, 0.0f, 0.0f));
	
	float rad = yawSlopeAngle * DX_PI_F / 180.0f;
	float c = std::cos(rad);
	float s = std::sin(rad);
	
	VECTOR axis_x = VAdd(VScale(direction, c), VScale(VCross(axis_z, direction), s));
	
	direction = pcs->GetDirection(VGet(0.0f, 1.0f, 0.0f));
	VECTOR axis_y = VAdd(VScale(direction, c), VScale(VCross(axis_z, direction), s));
	
	// 角速度設定
	VECTOR control_angularvelocity = VGet(axis_x.x * pitch + axis_y.x * yaw,
		axis_x.y * pitch + axis_y.y * yaw,
		axis_x.z * pitch + axis_y.z * yaw);
	
	float yawslopeangle_changeamount = current_yawslopeangle - yawSlopeAngle;
	VECTOR yawslope_angularvelocity = VGet(axis_z.x * yawslopeangle_changeamount,
		axis_z.y * yawslopeangle_changeamount,
		axis_z.z * yawslopeangle_changeamount);
	yawSlopeAngle = current_yawslopeangle;
	
	VECTOR angular_velocity = VAdd(control_angularvelocity, yawslope_angularvelocity);

	// 速度設定
	pcs->SetLinerVelocity(linear_velocity);
	pcs->SetAngularVelocity(angular_velocity);
}

float  Manual::VariableTransition_QuadraticIncrease(float ratio, float min, float max)
{
	if (ratio < 0.0f) { ratio = 0.0f; }
	if (ratio > 1.0f) { ratio = 1.0f; }

	return (max - min) * ratio * ratio + min;
}

float  Manual::VariableTransition_QuadraticDecrease(float ratio, float min, float max)
{
	if (ratio < 0.0f) { ratio = 0.0f; }
	if (ratio > 1.0f) { ratio = 1.0f; }

	return (min - max) * ratio * ratio + max;
}

float  Manual::VariableTransition_QuadraticFluctuation(float ratio, float min, float max)
{
	if (ratio < 0.0f) { ratio = 0.0f; }
	if (ratio > 1.0f) { ratio = 1.0f; }

	return ((min - max) / 0.25f) * (ratio - 0.5f) * (ratio - 0.5f) + max;
}