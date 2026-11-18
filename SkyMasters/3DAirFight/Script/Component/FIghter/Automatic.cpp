// ライブラリ・ヘッダ
#include <cmath>
#include "../../Math/VariableTransition.h"

#include "Fighter.h"
#include "Automatic.h"
#include "../../Screen/Screen.h"
#include "../../Actor/Actor.h"
#include "../Input.h"
#include "../PhysicsColliderSphere.h"
#include "../PhysicsColliderBox.h"
#include "../Transform.h"

// ターン
// trueの時継続
bool Automatic::Turn(float direction)
{
	if (direction < 0.0f)
	{
		direction = -1.0f;
	}
	else
	{
		direction = 1.0f;
	}

	switch (m_currentTurnState)
	{
	case Automatic::TurnState::SetUp:
		// 姿勢をニュートラルに戻す
		if (ReturnNeutralRoll())
		{
			m_currentTurnState = Automatic::TurnState::PitchTurn;
			m_pastTurnDot = 2.0f;
			PitchTurn(direction);
		}
		break;

	case Automatic::TurnState::PitchTurn:
		if (!PitchTurn(direction))
		{
			m_currentTurnState = Automatic::TurnState::RollTurn;
			m_pastTurnDot = 2.0f;
			RollTurn();
		}
		break;

	case Automatic::TurnState::RollTurn:
		if (!RollTurn())
		{
			m_currentTurnState = Automatic::TurnState::SetUp;
			m_pastTurnDot = 0.0f;
			return false;
		}
		break;

	default:
		break;
	}

	return true;
}

// ターンの現在状態の取得
Automatic::TurnState Automatic::GetCurrentTurnState() const
{
	return m_currentTurnState;
}

// ターンの進行値の取得
float Automatic::GetCurrentTurnValue() const
{
	return m_currentTurnValue;
}

// 機体のロールをニュートラルに戻す
// ニュートラルになったらtrue
bool Automatic::ReturnNeutralRoll()
{
	// 入力・物理コライダーの取得
	PhysicsColliderSphere* pcs = m_owner->GetComponent<PhysicsColliderSphere>();

	// 現在の姿勢取得
	VECTOR forward = pcs->GetDirection(VGet(0.0f, 0.0f, -1.0f));
	VECTOR down = pcs->GetDirection(VGet(0.0f, -1.0f, 0.0f));
	VECTOR right = pcs->GetDirection(VGet(1.0f, 0.0f, 0.0f));

	VECTOR reference_right = VNorm(VCross(forward, VGet(0.0f, 1.0f, 0.0f)));
	float dot = VDot(right, reference_right);

	// ピッチ・ヨー方向がニュートラルなら処理終了
	if (dot <= m_pastTurnDot)
	//Fighter* fighter = m_owner->GetComponent<Fighter>();
	//if(fighter->m_yawSlopeAngle == 0.0f)
	{
		pcs->SetLinerVelocity(VGet(0.0f, 0.0f, 0.0f));
		pcs->SetAngularVelocity(VGet(0.0f, 0.0f, 0.0f));
	
		Transform* tr = m_owner->GetComponent<Transform>();
	
		return true;
	}
	
	m_currentTurnValue = -VDot(VGet(0.0f, 1.0f, 0.0f), down);
	m_pastTurnDot = dot;

	// 自機の向きの取得
	float pitch_dot = VDot(VGet(0.0f, 1.0f, 0.0f), forward);

	// 自機制御コンポーネント取得
	Fighter* fighter = m_owner->GetComponent<Fighter>();

	// 速度設定
	VECTOR linear_velocity = VScale(forward, fighter->m_speed);

	// 角速度設定 & ヨー時の傾き設定
	float pitch = 0.0f;

	float current_yawslopeangle = 0.0f;
	float target_yawslopeangle = 0.0f;

	// ピッチの角速度設定
	//pitch = pitch_dot * (90.0f / fighter->m_pitchAngleMax) * fighter->m_pitchAngularVelocity;
	//
	//if (std::abs(pitch) < (fighter->m_pitchAngularVelocity) / 10.0f)
	//{
	//	if (pitch_dot > 0.0f)
	//	{
	//		pitch = (fighter->m_pitchAngularVelocity) / 10.0f;
	//	}
	//	else if (pitch_dot < 0.0f)
	//	{
	//		pitch = -(fighter->m_pitchAngularVelocity) / 10.0f;
	//	}
	//	else
	//	{
	//		pitch = 0.0f;
	//	}
	//}

	// ヨーの傾き設定
	if (target_yawslopeangle > fighter->m_yawSlopeAngle)
	{
		float spd = VariableTransition_QuadraticFluctuation((target_yawslopeangle - fighter->m_yawSlopeAngle) / (fighter->m_yawSlopeAngleMax * 2.0f),
			fighter->m_yawSlopeAngleSpeedMin, fighter->m_yawSlopeAngleSpeedMax);
		current_yawslopeangle = fighter->m_yawSlopeAngle + spd / Screen::FPS;
		if (current_yawslopeangle > target_yawslopeangle)
		{
			current_yawslopeangle = target_yawslopeangle;
		}
	}
	else if (target_yawslopeangle < fighter->m_yawSlopeAngle)
	{
		float spd = VariableTransition_QuadraticFluctuation((fighter->m_yawSlopeAngle - target_yawslopeangle) / (fighter->m_yawSlopeAngleMax * 2.0f),
			fighter->m_yawSlopeAngleSpeedMin, fighter->m_yawSlopeAngleSpeedMax);
		current_yawslopeangle = fighter->m_yawSlopeAngle - spd / Screen::FPS;
		if (current_yawslopeangle < target_yawslopeangle)
		{
			current_yawslopeangle = target_yawslopeangle;
		}
	}
	else
	{
		current_yawslopeangle = target_yawslopeangle;
	}

	// 機体の軸方向設定
	VECTOR axis_z = VScale(forward, -1.0f);
	//VECTOR direction = pcs->GetDirection(VGet(1.0f, 0.0f, 0.0f));
	//
	//float rad = fighter->m_yawSlopeAngle * DX_PI_F / 180.0f;
	//float c = std::cos(rad);
	//float s = std::sin(rad);
	//
	//VECTOR axis_x = VAdd(VScale(direction, c), VScale(VCross(axis_z, direction), s));
	//
	//// 角速度設定
	//VECTOR control_angularvelocity = VGet(axis_x.x * pitch,
	//	axis_x.y * pitch,
	//	axis_x.z * pitch);

	float yawslopeangle_changeamount = current_yawslopeangle - fighter->m_yawSlopeAngle;
	VECTOR yawslope_angularvelocity = VGet(axis_z.x * yawslopeangle_changeamount,
		axis_z.y * yawslopeangle_changeamount,
		axis_z.z * yawslopeangle_changeamount);
	fighter->m_yawSlopeAngle = current_yawslopeangle;

	//if (yawslopeangle_changeamount == 0.0f)
	//{
	//	pcs->SetLinerVelocity(VGet(0.0f, 0.0f, 0.0f));
	//	pcs->SetAngularVelocity(VGet(0.0f, 0.0f, 0.0f));
	//
	//	Transform* tr = m_owner->GetComponent<Transform>();
	//
	//	return true;
	//}
	//
	//m_currentTurnValue = -VDot(VGet(0.0f, 1.0f, 0.0f), down);
	//m_pastTurnDot = dot;

	//VECTOR angular_velocity = VAdd(control_angularvelocity, yawslope_angularvelocity);

	// 速度設定
	pcs->SetLinerVelocity(linear_velocity);
	pcs->SetAngularVelocity(yawslope_angularvelocity);

	return false;
}

// 宙返り
// trueの時継続
bool Automatic::PitchTurn(float turn_direction)
{
	// 入力・物理コライダーの取得
	PhysicsColliderSphere* pcs = m_owner->GetComponent<PhysicsColliderSphere>();

	// 自機の向きの取得
	VECTOR forward = pcs->GetDirection(VGet(0.0f, 0.0f, -1.0f));
	VECTOR up = pcs->GetDirection(VGet(0.0f, 1.0f, 0.0f));

	// 現在の姿勢取得
	float pitch_dot = VDot(VGet(0.0f, 1.0f, 0.0f), up);

	// 機体がひっくり返っていたなら処理終了
	if (pitch_dot >= m_pastTurnDot)
	{
		pcs->SetLinerVelocity(VGet(0.0f, 0.0f, 0.0f));
		pcs->SetAngularVelocity(VGet(0.0f, 0.0f, 0.0f));
		return false;
	}

	m_currentTurnValue = -pitch_dot;
	m_pastTurnDot = pitch_dot;

	// 自機制御コンポーネント取得
	Fighter* fighter = m_owner->GetComponent<Fighter>();

	// 速度設定
	VECTOR linear_velocity = VScale(forward, fighter->m_speed);

	float pitch = fighter->m_pitchAngularVelocity * -turn_direction;

	// 機体の軸方向設定
	VECTOR axis_z = VScale(forward, -1.0f);
	VECTOR direction = pcs->GetDirection(VGet(1.0f, 0.0f, 0.0f));

	float rad = fighter->m_yawSlopeAngle * DX_PI_F / 180.0f;
	float c = std::cos(rad);
	float s = std::sin(rad);

	VECTOR axis_x = VAdd(VScale(direction, c), VScale(VCross(axis_z, direction), s));

	// 角速度設定
	VECTOR angular_velocity = VGet(axis_x.x * pitch,
		axis_x.y * pitch,
		axis_x.z * pitch);

	// 速度設定
	pcs->SetLinerVelocity(linear_velocity);
	pcs->SetAngularVelocity(angular_velocity);

	return true;
}

// ロール方向にターン
// trueの時継続
bool Automatic::RollTurn()
{
	// 入力・物理コライダーの取得
	PhysicsColliderSphere* pcs = m_owner->GetComponent<PhysicsColliderSphere>();

	// 自機の向きの取得
	VECTOR forward = pcs->GetDirection(VGet(0.0f, 0.0f, -1.0f));
	VECTOR down = pcs->GetDirection(VGet(0.0f, -1.0f, 0.0f));

	// 現在の姿勢取得
	float dot = VDot(VGet(0.0f, 1.0f, 0.0f), down);

	// 機体がひっくり返っていたなら処理終了
	if (dot >= m_pastTurnDot)
	{
		// ロール0度時の右方向
		VECTOR reference_right = VNorm(VCross(forward, VGet(0.0f, 1.0f, 0.0f)));

		// ロール0度時の上方向
		VECTOR reference_up = VNorm(VCross(reference_right, forward));

		VECTOR up = pcs->GetDirection(VGet(0.0f, 1.0f, 0.0f));

		float sin_roll = VDot(up, reference_up);

		float cos_roll = VDot(up, VGet(0.0f, 1.0f, 0.0f));

		float roll = atan2f(sin_roll, cos_roll);

		VECTOR rotationAxis = forward;
		float rotationAngle = -roll;

		// 角速度設定
		VECTOR angular_velocity = VScale(rotationAxis, rotationAngle);
		pcs->SetAngularVelocity(angular_velocity);

		return false;
	}

	m_currentTurnValue = -dot / 2.0f - 0.5f;
	m_pastTurnDot = dot;

	// 自機制御コンポーネント取得
	Fighter* fighter = m_owner->GetComponent<Fighter>();

	// 速度設定
	VECTOR linear_velocity = VScale(forward, fighter->m_speed);

	// 機体の軸方向設定
	VECTOR axis_z = VScale(forward, -1.0f);

	// 角速度設定
	float roll = 1.0f;

	VECTOR angular_velocity = VGet(axis_z.x * roll,
		axis_z.y * roll,
		axis_z.z * roll);

	pcs->SetAngularVelocity(angular_velocity);

	// 速度設定
	pcs->SetLinerVelocity(linear_velocity);

	return true;
}
