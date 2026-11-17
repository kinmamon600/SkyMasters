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

// 機体の向きをニュートラルに戻す
// ニュートラルになったらtrue
bool Automatic::ReturnNeutral()
{
	// 入力・物理コライダーの取得
	PhysicsColliderSphere* pcs = m_owner->GetComponent<PhysicsColliderSphere>();

	// 現在の姿勢取得
	VECTOR down = pcs->GetDirection(VGet(0.0f, -1.0f, 0.0f));
	float dot = VDot(VGet(0.0f, 1.0f, 0.0f), down);

	// 機体がひっくり返っていたなら処理終了
	if (dot >= m_pastTurnDot)
	{
		m_pastTurnDot = 2.0f;
		pcs->SetLinerVelocity(VGet(0.0f, 0.0f, 0.0f));
		pcs->SetAngularVelocity(VGet(0.0f, 0.0f, 0.0f));
		return true;
	}

	m_currentTurnValue = -dot;
	m_pastTurnDot = dot;

	// 自機の向きの取得
	VECTOR forward = pcs->GetDirection(VGet(0.0f, 0.0f, -1.0f));
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
	pitch = pitch_dot * (90.0f / fighter->m_pitchAngleMax) * fighter->m_pitchAngularVelocity;

	if (std::abs(pitch) < (fighter->m_pitchAngularVelocity) / 10.0f)
	{
		if (pitch_dot > 0.0f)
		{
			pitch = (fighter->m_pitchAngularVelocity) / 10.0f;
		}
		else if (pitch_dot < 0.0f)
		{
			pitch = -(fighter->m_pitchAngularVelocity) / 10.0f;
		}
		else
		{
			pitch = 0.0f;
		}
	}
	
	// ヨーの傾き設定
	target_yawslopeangle = 0;

	if (target_yawslopeangle > fighter->m_yawSlopeAngle)
	{
		float spd = VariableTransition_QuadraticFluctuation((target_yawslopeangle - fighter->m_yawSlopeAngle) / (fighter->m_yawSlopeAngleMax * 2.0f),
			fighter->m_yawSlopeAngleSpeedMin, fighter->m_yawSlopeAngleSpeedMax);
		current_yawslopeangle = fighter->m_yawSlopeAngle + spd / Screen::FPS;
		if (current_yawslopeangle > target_yawslopeangle) { current_yawslopeangle = target_yawslopeangle; }
	}
	else if (target_yawslopeangle < fighter->m_yawSlopeAngle)
	{
		float spd = VariableTransition_QuadraticFluctuation((fighter->m_yawSlopeAngle - target_yawslopeangle) / (fighter->m_yawSlopeAngleMax * 2.0f),
			fighter->m_yawSlopeAngleSpeedMin, fighter->m_yawSlopeAngleSpeedMax);
		current_yawslopeangle = fighter->m_yawSlopeAngle - spd / Screen::FPS;
		if (current_yawslopeangle < target_yawslopeangle) { current_yawslopeangle = target_yawslopeangle; }
	}
	else
	{
		current_yawslopeangle = target_yawslopeangle;
	}

	// 機体の軸方向設定
	VECTOR axis_z = VScale(forward, -1.0f);
	VECTOR direction = pcs->GetDirection(VGet(1.0f, 0.0f, 0.0f));

	float rad = fighter->m_yawSlopeAngle * DX_PI_F / 180.0f;
	float c = std::cos(rad);
	float s = std::sin(rad);

	VECTOR axis_x = VAdd(VScale(direction, c), VScale(VCross(axis_z, direction), s));

	// 角速度設定
	VECTOR control_angularvelocity = VGet(axis_x.x * pitch,
		axis_x.y * pitch,
		axis_x.z * pitch);

	float yawslopeangle_changeamount = current_yawslopeangle - fighter->m_yawSlopeAngle;
	VECTOR yawslope_angularvelocity = VGet(axis_z.x * yawslopeangle_changeamount,
		axis_z.y * yawslopeangle_changeamount,
		axis_z.z * yawslopeangle_changeamount);
	fighter->m_yawSlopeAngle = current_yawslopeangle;

	VECTOR angular_velocity = VAdd(control_angularvelocity, yawslope_angularvelocity);

	// 速度設定
	pcs->SetLinerVelocity(linear_velocity);
	pcs->SetAngularVelocity(angular_velocity);

	return false;
}

// ターン
// trueの時継続
bool Automatic::Turn()
{
	switch (m_currentTurnState)
	{
	case Automatic::TurnState::SetUp:
		// 姿勢をニュートラルに戻す
		if (ReturnNeutral())
		{
			m_currentTurnState = Automatic::TurnState::PitchTurn;
			PitchTurn();
		}
		break;

	case Automatic::TurnState::PitchTurn:
		if (!PitchTurn())
		{
			m_currentTurnState = Automatic::TurnState::RollTurn;
			RollTurn();
		}
		break;

	case Automatic::TurnState::RollTurn:
		// 姿勢をニュートラルに戻す
		if (!RollTurn())
		{
			m_currentTurnState = Automatic::TurnState::SetUp;
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

// 宙返り
// trueの時継続
bool Automatic::PitchTurn()
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
		m_pastTurnDot = 2.0f;
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

	float pitch = -fighter->m_pitchAngularVelocity;

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

// ロールしてニュートラルに戻る
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
	//if (dot <= -1.0f)
	if (dot >= m_pastTurnDot)
	{
		m_pastTurnDot = 2.0f;
		pcs->SetLinerVelocity(VGet(0.0f, 0.0f, 0.0f));
		pcs->SetAngularVelocity(VGet(0.0f, 0.0f, 0.0f));
		return false;
	}

	m_currentTurnValue = -dot / 2.0f - 0.5f;
	m_pastTurnDot = dot;

	// 自機制御コンポーネント取得
	Fighter* fighter = m_owner->GetComponent<Fighter>();

	// 速度設定
	VECTOR linear_velocity = VScale(forward, fighter->m_speed);

	float roll = fighter->m_rollAngularVelocityMax * (-m_currentTurnValue + fighter->m_rollAngularVelocityMin);

	// 機体の軸方向設定
	VECTOR axis_z = VScale(forward, -1.0f);
	
	// 角速度設定
	VECTOR angular_velocity = VGet(axis_z.x * roll,
		axis_z.y * roll,
		axis_z.z * roll);

	// 速度設定
	pcs->SetLinerVelocity(linear_velocity);
	pcs->SetAngularVelocity(angular_velocity);

	return true;
}
