// ライブラリ・ヘッダ
#include <cmath>

#include "../Camera.h"
#include "Automatic.h"
#include "AutomaticCamera.h"
#include "../../Actor/Actor.h"
#include"../../Screen/Screen.h"
#include "../Transform.h"
#include "Fighter.h"
#include "../PhysicsColliderSphere.h"

// ターン時のカメラ制御
void AutomaticCamera::TurnCamera(const Fighter* p_player_fighter, const Automatic* p_player_automatic, PhysicsCollider* p_player_pc, const Transform* p_player_tr)
{
	switch (p_player_automatic->GetCurrentTurnState())
	{
	case Automatic::TurnState::SetUp:
		ReturnNeutral(p_player_fighter, p_player_automatic, p_player_pc, p_player_tr);
		break;

	case Automatic::TurnState::PitchTurn:
		PitchTurn(p_player_fighter, p_player_automatic, p_player_pc, p_player_tr);
		break;

	case Automatic::TurnState::RollTurn:
		RollTurn(p_player_fighter, p_player_automatic, p_player_pc, p_player_tr);
		break;

	default:
		break;
	}
}

// ニュートラル位置に戻す(マニュアル操作との繋ぎ)
void AutomaticCamera::ReturnNeutral(const Fighter* p_player_fighter, const Automatic* p_player_automatic, PhysicsCollider* p_player_pc, const Transform* p_player_tr)
{
	// カメラコンポーネントと座標の取得
	Camera* camera = m_owner->GetComponent<Camera>();
	VECTOR camera_pos = camera->GetPosition();

	// ターゲット座標の設定
	// 自機の座標と向きの取得
	VECTOR fighter_pos = p_player_tr->GetPosition();
	VECTOR fighter_forward = p_player_pc->GetDirection(VGet(0.0f, 0.0f, -1.0f));

	// 注視点の設定
	VECTOR fixation_pos = VNorm(VGet(fighter_forward.x, 0, fighter_forward.z));
	fixation_pos = VAdd(VScale(fixation_pos, p_player_fighter->m_cameraFixationOffset), fighter_pos);

	VECTOR target_pos = VNorm(VGet(-fighter_forward.x, 0, -fighter_forward.z));

	// カメラをロドリゲスの回転公式で自機正面が見えるよう位置調整
	VECTOR axis = p_player_pc->GetDirection(VGet(1.0f, 0.0f, 0.0f));
	float rad = ((-p_player_fighter->m_cameraDefaultPitchAngle)) * DX_PI_F / 180.0f;
	float c = std::cos(rad);
	float s = std::sin(rad);
	target_pos = VAdd(VScale(target_pos, c), VScale(VCross(axis, target_pos), s));

	axis = VGet(0.0f, 1.0f, 0.0f);
	rad = 0.0f;
	c = std::cos(rad);
	s = std::sin(rad);
	target_pos = VAdd(VScale(target_pos, c), VScale(VCross(axis, target_pos), s));

	target_pos = VAdd(VScale(target_pos, p_player_fighter->m_cameraDistance), fixation_pos);

	// カメラ座標の設定
	float move_value = p_player_fighter->m_cameraAutomaticSpeed / Screen::FPS;
	VECTOR vec = VAdd(target_pos, VScale(camera_pos, -1.0f));

	if (std::abs(VSize(vec)) > move_value)
	{
		vec = VScale(VNorm(vec), move_value);
	}

	camera_pos = VAdd(camera_pos, vec);

	m_correctionValueY = camera_pos.y - fighter_pos.y;

	camera->SetPosition(camera_pos);
	camera->SetTarget(fixation_pos);
}

// ピッチターン時のカメラ制御
void AutomaticCamera::PitchTurn(const Fighter* p_player_fighter, const Automatic* p_player_automatic, PhysicsCollider* p_player_pc, const Transform* p_player_tr)
{
	// カメラコンポーネントと座標の取得
	Camera* camera = m_owner->GetComponent<Camera>();
	VECTOR camera_pos = camera->GetPosition();

	// 自機の座標の取得
	VECTOR fighter_pos = p_player_tr->GetPosition();
	VECTOR fighter_forward = p_player_pc->GetDirection(VGet(0.0f, 0.0f, -1.0f));

	// 注視点の設定
	VECTOR fixation_pos = VNorm(VGet(fighter_forward.x, 0, fighter_forward.z));
	fixation_pos = VAdd(VScale(fixation_pos, p_player_fighter->m_cameraFixationOffset), fighter_pos);

	// カメラ設定
	float correction_y = 0.0f;

	if (p_player_automatic->GetCurrentTurnValue() < 0.0f)
	{
		correction_y = p_player_automatic->GetCurrentTurnValue() * p_player_automatic->GetCurrentTurnValue() * (std::abs(m_correctionValueY_Min) + 1.0f) + m_correctionValueY_Min;
		fixation_pos = VAdd(fixation_pos, VScale(VAdd(fighter_pos, VScale(fixation_pos, -1.0f)), 1.0f - std::abs(p_player_automatic->GetCurrentTurnValue())));
		camera->SetTarget(fixation_pos);
	}
	else
	{
		correction_y = p_player_automatic->GetCurrentTurnValue() * p_player_automatic->GetCurrentTurnValue() * (m_correctionValueY_Max - m_correctionValueY_Min) + m_correctionValueY_Min;
		camera->SetTarget(fighter_pos);
	}

	camera_pos = VGet(camera_pos.x, fighter_pos.y + (correction_y * m_correctionValueY), camera_pos.z);
	camera->SetPosition(camera_pos);
}

// ロールターン時のカメラ制御
void AutomaticCamera::RollTurn(const Fighter* p_player_fighter, const Automatic* p_player_automatic, PhysicsCollider* p_player_pc, const Transform* p_player_tr)
{
	// カメラコンポーネントと座標の取得
	Camera* camera = m_owner->GetComponent<Camera>();
	VECTOR camera_pos = camera->GetPosition();

	// ターゲット座標の設定
	// 自機の座標と向きの取得
	VECTOR fighter_pos = p_player_tr->GetPosition();
	VECTOR fighter_forward = p_player_pc->GetDirection(VGet(0.0f, 0.0f, -1.0f));

	// 注視点の設定
	VECTOR fixation_pos = VNorm(VGet(fighter_forward.x, 0, fighter_forward.z));
	fixation_pos = VAdd(VScale(fixation_pos, p_player_fighter->m_cameraFixationOffset), fighter_pos);

	VECTOR target_pos = VNorm(VGet(-fighter_forward.x, 0, -fighter_forward.z));

	// カメラをロドリゲスの回転公式で自機正面が見えるよう位置調整
	VECTOR axis = p_player_pc->GetDirection(VGet(1.0f, 0.0f, 0.0f));
	float rad = ((-p_player_fighter->m_cameraDefaultPitchAngle)) * DX_PI_F / 180.0f;
	float c = std::cos(rad);
	float s = std::sin(rad);
	target_pos = VAdd(VScale(target_pos, c), VScale(VCross(axis, target_pos), s));

	axis = VGet(0.0f, 1.0f, 0.0f);
	rad = 0.0f;
	c = std::cos(rad);
	s = std::sin(rad);
	target_pos = VAdd(VScale(target_pos, c), VScale(VCross(axis, target_pos), s));

	target_pos = VAdd(VScale(target_pos, p_player_fighter->m_cameraDistance), fixation_pos);

	// カメラ座標の設定
	float move_value = p_player_fighter->m_cameraAutomaticSpeed / Screen::FPS;
	VECTOR vec = VAdd(target_pos, VScale(camera_pos, -1.0f));

	if (std::abs(VSize(vec)) > move_value)
	{
		vec = VScale(VNorm(vec), move_value);
	}

	camera_pos = VAdd(camera_pos, vec);

	fixation_pos = VAdd(fighter_pos, VScale(VAdd(fixation_pos, VScale(fighter_pos, -1.0f)), 1.0f - std::abs(p_player_automatic->GetCurrentTurnValue())));
	
	camera->SetPosition(camera_pos);
	camera->SetTarget(fixation_pos);
}
