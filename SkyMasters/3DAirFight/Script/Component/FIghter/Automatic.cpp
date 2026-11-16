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
	m_currentTurnValue = -dot;
	//printfDx("%f\n", m_currentTurnValue);

	// 機体がひっくり返っていたなら処理終了
	if (dot < -0.99f)
	{
		pcs->SetLinerVelocity(VGet(0.0f, 0.0f, 0.0f));
		pcs->SetAngularVelocity(VGet(0.0f, 0.0f, 0.0f));
		return true;
	}

	// 自機の向きの取得
	VECTOR forward = pcs->GetDirection(VGet(0.0f, 0.0f, -1.0f));
	float pitch_dot = VDot(VGet(0.0f, 1.0f, 0.0f), forward);

	// 自機制御コンポーネント取得
	Fighter* fighter = m_owner->GetComponent<Fighter>();

	// 速度設定
	VECTOR linear_velocity = VScale(forward, fighter->speed);

	// 角速度設定 & ヨー時の傾き設定
	// プレイヤー操作時で無ければ0
	float pitch = 0.0f;

	float current_yawslopeangle = 0.0f;
	float target_yawslopeangle = 0.0f;

	// ピッチの角速度設定
	float pitch_target = 0;
	pitch = (pitch_dot - pitch_target) * (90.0f / fighter->pitchAngleMax) * (fighter->pitchAngularVelocity);
	
	// ヨーの傾き設定
	target_yawslopeangle = 0;

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

	// 角速度設定
	VECTOR control_angularvelocity = VGet(axis_x.x * pitch,
		axis_x.y * pitch,
		axis_x.z * pitch);

	float yawslopeangle_changeamount = current_yawslopeangle - fighter->yawSlopeAngle;
	VECTOR yawslope_angularvelocity = VGet(axis_z.x * yawslopeangle_changeamount,
		axis_z.y * yawslopeangle_changeamount,
		axis_z.z * yawslopeangle_changeamount);
	fighter->yawSlopeAngle = current_yawslopeangle;

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
		}
		break;

	case Automatic::TurnState::PitchTurn:
		if (!PitchTurn())
		{
			m_currentTurnState = Automatic::TurnState::RollTurn;
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
	if (pitch_dot < -0.99f)
	{
		pcs->SetLinerVelocity(VGet(0.0f, 0.0f, 0.0f));
		pcs->SetAngularVelocity(VGet(0.0f, 0.0f, 0.0f));
		return false;
	}

	// 自機制御コンポーネント取得
	Fighter* fighter = m_owner->GetComponent<Fighter>();

	// 速度設定
	VECTOR linear_velocity = VScale(forward, fighter->speed);

	float pitch = -fighter->pitchAngularVelocity;

	// 機体の軸方向設定
	VECTOR axis_z = VScale(forward, -1.0f);
	VECTOR direction = pcs->GetDirection(VGet(1.0f, 0.0f, 0.0f));

	float rad = fighter->yawSlopeAngle * DX_PI_F / 180.0f;
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
	m_currentTurnValue = -dot / 2.0f - 0.5f;

	// 機体がひっくり返っていたなら処理終了
	if (dot < -0.99f)
	{
		pcs->SetLinerVelocity(VGet(0.0f, 0.0f, 0.0f));
		pcs->SetAngularVelocity(VGet(0.0f, 0.0f, 0.0f));
		return false;
	}

	// 自機制御コンポーネント取得
	Fighter* fighter = m_owner->GetComponent<Fighter>();

	// 速度設定
	VECTOR linear_velocity = VScale(forward, fighter->speed);

	float roll = fighter->rollAngularVelocity;

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
