// ライブラリ・ヘッダ
#include <cmath>
#include "../../Math/VariableTransition.h"

#include "Fighter.h"
#include "Manual.h"
#include "../../Screen/Screen.h"
#include "../../Actor/Actor.h"
#include "../Input.h"
#include "../../Input/ControllerInput.h"
#include "../PhysicsColliderSphere.h"
#include "../PhysicsColliderBox.h"

VECTOR Manual::FighterControl()
{
	// どのくらい動いているかを -1.0f ~ 1.0f で返す
	float result_x = 0.0f;
	float result_y = 0.0f;

	// 自機制御コンポーネント取得
	Fighter* fighter = m_owner->GetComponent<Fighter>();

	// 入力・物理コライダーの取得
	Input* input = m_owner->GetComponent<Input>();
	PhysicsColliderSphere* pcs = m_owner->GetComponent<PhysicsColliderSphere>();

	// 自機の向きの取得
	VECTOR forward = pcs->GetDirection(VGet(0.0f, 0.0f, -1.0f));

	// 速度設定
<<<<<<< HEAD
	VECTOR linear_velocity = VScale(forward, fighter->speed);
=======
	// hpが0なら0
	VECTOR linear_velocity = VScale(forward, speed);
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
	float pitch_target = (1.0f - std::abs(pitch_dot)) * (fighter->pitchAngleMax / 180.0f * DX_PI) * (float)(input->GetAnalog(Input::LY)) / ANALOG_INPUT_MAX;
	pitch = (pitch_dot - pitch_target) * (90.0f / fighter->pitchAngleMax) * fighter->pitchAngularVelocity;
	result_y = pitch_dot * (90.0f / fighter->pitchAngleMax);

	// ヨーの角速度設定
	yaw = -(float)(input->GetAnalog(Input::LX)) / ANALOG_INPUT_MAX * fighter->yawAngularVelocity;
	
	// ヨーの傾き設定
	target_yawslopeangle = -(float)(input->GetAnalog(Input::LX)) / ANALOG_INPUT_MAX * fighter->yawSlopeAngleMax;
	
	if (target_yawslopeangle > fighter->yawSlopeAngle)
	{
		float spd = VariableTransition_QuadraticFluctuation((target_yawslopeangle - fighter->yawSlopeAngle) / (fighter->yawSlopeAngleMax * 2.0f),
			fighter->yawSlopeAngleSpeedMin, fighter->yawSlopeAngleSpeedMax);
		current_yawslopeangle = fighter->yawSlopeAngle + spd / Screen::FPS;
		if (current_yawslopeangle > target_yawslopeangle) { current_yawslopeangle = target_yawslopeangle; }
	}
	else if (target_yawslopeangle < fighter->yawSlopeAngle)
	{
		float spd = VariableTransition_QuadraticFluctuation((fighter->yawSlopeAngle - target_yawslopeangle) / (fighter->yawSlopeAngleMax * 2.0f),
			fighter->yawSlopeAngleSpeedMin, fighter->yawSlopeAngleSpeedMax);
		current_yawslopeangle = fighter->yawSlopeAngle - spd / Screen::FPS;
		if (current_yawslopeangle < target_yawslopeangle) { current_yawslopeangle = target_yawslopeangle; }
	}
	else
	{
		current_yawslopeangle = target_yawslopeangle;
	}
	
	// 機体の軸方向設定
	VECTOR axis_z = VScale(forward, -1.0f);
	VECTOR direction = pcs->GetDirection(VGet(1.0f, 0.0f, 0.0f));
	
	float rad = fighter->yawSlopeAngle * DX_PI_F / 180.0f;
	float c = std::cos(rad);
	float s = std::sin(rad);
	
	VECTOR axis_x = VAdd(VScale(direction, c), VScale(VCross(axis_z, direction), s));
	
	direction = pcs->GetDirection(VGet(0.0f, 1.0f, 0.0f));
	VECTOR axis_y = VGet(0.0f, 1.0f, 0.0f);
	
	// 角速度設定
	VECTOR control_angularvelocity = VGet(axis_x.x * pitch + axis_y.x * yaw,
		axis_x.y * pitch + axis_y.y * yaw,
		axis_x.z * pitch + axis_y.z * yaw);
	
	float yawslopeangle_changeamount = current_yawslopeangle - fighter->yawSlopeAngle;
	VECTOR yawslope_angularvelocity = VGet(axis_z.x * yawslopeangle_changeamount,
		axis_z.y * yawslopeangle_changeamount,
		axis_z.z * yawslopeangle_changeamount);
	fighter->yawSlopeAngle = current_yawslopeangle;
	
	VECTOR angular_velocity = VAdd(control_angularvelocity, yawslope_angularvelocity);

	// 速度設定
	pcs->SetLinerVelocity(linear_velocity);
	pcs->SetAngularVelocity(angular_velocity);

	// 返り値設定
	result_x = -fighter->yawSlopeAngle / fighter->yawSlopeAngleMax;
	VECTOR result = VGet(result_x, -result_y, 0);
	if (VSize(result) > 1.0f)
	{
		result = VNorm(result);
	}

	//printfDx("%f, %f\n", result.x, result.y);
	return result;
}
