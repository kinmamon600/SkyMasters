// ライブラリ・ヘッダ
#include <cmath>
#include "../../Math/VariableTransition.h"

#include "Fighter.h"
#include "Automatic.h"
#include "../../Screen/Screen.h"
#include "../../Actor/Actor.h"
#include "../Input.h"
#include "../PhysicsCollider.h"
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
		if (ReturnNeutral())
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

// 機体をニュートラルに戻す
// ニュートラルになったらtrue
bool Automatic::ReturnNeutral()
{
	// 入力・物理コライダーの取得
	PhysicsCollider* pcs = m_owner->GetComponent<PhysicsCollider>();

	// 現在の姿勢取得
	VECTOR forward = pcs->GetDirection(VGet(0.0f, 0.0f, -1.0f));
	VECTOR down = pcs->GetDirection(VGet(0.0f, -1.0f, 0.0f));
	VECTOR right = pcs->GetDirection(VGet(1.0f, 0.0f, 0.0f));

	VECTOR reference_right = VNorm(VCross(forward, VGet(0.0f, 1.0f, 0.0f)));
	float dot = VDot(right, reference_right);

	// 自機制御コンポーネント取得
	Fighter* fighter = m_owner->GetComponent<Fighter>();

	fighter->m_currentSpeed -= (fighter->m_deceleration / Screen::FPS);

	if (fighter->m_currentSpeed < fighter->m_minSpeed)
	{
		fighter->m_currentSpeed = fighter->m_minSpeed;
	}

	// ピッチ・ヨー方向がニュートラルなら処理終了
	if (dot <= m_pastTurnDot && (fighter->m_currentSpeed == fighter->m_minSpeed))
	{
		pcs->SetLinerVelocity(VGet(0.0f, 0.0f, 0.0f));
		pcs->SetAngularVelocity(VGet(0.0f, 0.0f, 0.0f));
	
		fighter->m_yawSlopeAngle = 0.0f;
		Transform* tr = m_owner->GetComponent<Transform>();
		VECTOR rote = tr->GetRotation();
		tr->SetRotation(CutPitchRoll(rote));
	
		return true;
	}
	
	m_currentTurnValue = -VDot(VGet(0.0f, 1.0f, 0.0f), down);
	m_pastTurnDot = dot;

	// 自機の向きの取得
	float pitch_dot = VDot(VGet(0.0f, 1.0f, 0.0f), forward);

	// 速度設定
	VECTOR linear_velocity = VScale(forward, fighter->m_currentSpeed);

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
	float yawslopeangle_changeamount = current_yawslopeangle - fighter->m_yawSlopeAngle;
	
	VECTOR axis_z = VScale(forward, -1.0f);
	VECTOR direction = pcs->GetDirection(VGet(1.0f, 0.0f, 0.0f));

	float rad = fighter->m_yawSlopeAngle * DX_PI_F / 180.0f;
	float c = std::cos(rad);
	float s = std::sin(rad);

	VECTOR axis_x = VAdd(VScale(direction, c), VScale(VCross(axis_z, direction), s));

	// 角速度設定
	VECTOR angularvelocity = VGet(axis_x.x * pitch + axis_z.x * yawslopeangle_changeamount,
		axis_x.y * pitch + axis_z.y * yawslopeangle_changeamount,
		axis_x.z * pitch + axis_z.z * yawslopeangle_changeamount);
	fighter->m_yawSlopeAngle = current_yawslopeangle;

	// 速度設定
	pcs->SetLinerVelocity(linear_velocity);
	pcs->SetAngularVelocity(angularvelocity);

	return false;
}

// 宙返り
// trueの時継続
bool Automatic::PitchTurn(float turn_direction)
{
	// 入力・物理コライダーの取得
	PhysicsCollider* pcs = m_owner->GetComponent<PhysicsCollider>();

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
	fighter->m_currentSpeed = fighter->m_minSpeed;
	VECTOR linear_velocity = VScale(forward, fighter->m_currentSpeed);

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
	PhysicsCollider* pcs = m_owner->GetComponent<PhysicsCollider>();

	// 自機の向きの取得
	VECTOR forward = pcs->GetDirection(VGet(0.0f, 0.0f, -1.0f));
	VECTOR down = pcs->GetDirection(VGet(0.0f, -1.0f, 0.0f));

	// 現在の姿勢取得
	float dot = VDot(VGet(0.0f, 1.0f, 0.0f), down);

	// 自機制御コンポーネント取得
	Fighter* fighter = m_owner->GetComponent<Fighter>();

	// 機体がひっくり返っていたなら処理終了
	if (dot >= m_pastTurnDot)
	{
		pcs->SetLinerVelocity(VGet(0.0f, 0.0f, 0.0f));
		pcs->SetAngularVelocity(VGet(0.0f, 0.0f, 0.0f));

		fighter->m_yawSlopeAngle = 0.0f;
		fighter->m_currentSpeed = fighter->m_defaultSpeed;
		Transform* tr = m_owner->GetComponent<Transform>();
		VECTOR rote = tr->GetRotation();
		tr->SetRotation(CutPitchRoll(rote));

		return false;
	}

	m_currentTurnValue = -dot / 2.0f - 0.5f;
	m_pastTurnDot = dot;
	
	// 速度設定
	fighter->m_currentSpeed = fighter->m_minSpeed + (fighter->m_defaultSpeed - fighter->m_minSpeed) * (1.0f + m_currentTurnValue);
	VECTOR linear_velocity = VScale(forward, fighter->m_currentSpeed);
	pcs->SetLinerVelocity(linear_velocity);

	float roll = fighter->m_rollAngularVelocityMax * (-m_currentTurnValue + fighter->m_rollAngularVelocityMin);

	// 機体の軸方向設定
	VECTOR axis_z = VScale(forward, -1.0f);

	// 角速度設定
	VECTOR angular_velocity = VGet(axis_z.x * roll,
		axis_z.y * roll,
		axis_z.z * roll);

	// 速度設定
	pcs->SetAngularVelocity(angular_velocity);

	return true;
}

// 回転のピッチ・ロールをカットする(ヨーのみにして地面と水平にする)
VECTOR Automatic::CutPitchRoll(VECTOR rote)
{
	//printfDx("元　:%f, %f, %f\n", rote.x, rote.y, rote.z);

	if (fabsf(rote.x) < 90.0f)
	{
		rote.x = 0.0f;
	}
	else if (fabsf(rote.x - 180.0f) < 90.0f)
	{
		rote.x = 180.0f;
	}
	else if (fabsf(rote.x + 180.0f) < 90.0f)
	{
		rote.x = -180.0f;
	}
	
	if (fabsf(rote.z) < 90.0f)
	{
		rote.z = 0.0f;
	}
	else if (fabsf(rote.z - 180.0f) < 90.0f)
	{
		rote.z = 180.0f;
	}
	else if (fabsf(rote.z + 180.0f) < 90.0f)
	{
		rote.z = -180.0f;
	}

	//rote = VGet((float)(((int)rote.x + 180) / 360) * 360.0f, rote.y, (float)(((int)rote.z + 180) / 360) * 360.0f);
	//printfDx("変換:%f, %f, %f\n\n", rote.x, rote.y, rote.z);
	return rote;
}
