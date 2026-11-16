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
void AutomaticCamera::TurnCamera(const Fighter* p_player_fighter, const Automatic* p_player_automatic, PhysicsColliderSphere* p_player_pc, const Transform* p_player_tr)
{
	switch (p_player_automatic->GetCurrentTurnState())
	{
	case Automatic::TurnState::SetUp:
		ReturnNeutral(p_player_fighter, p_player_automatic, p_player_pc, p_player_tr);
		break;

	case Automatic::TurnState::PitchTurn:
		PitchTurn(p_player_fighter, p_player_automatic, p_player_tr);
		break;

	case Automatic::TurnState::RollTurn:
		ReturnNeutral(p_player_fighter, p_player_automatic, p_player_pc, p_player_tr);
		break;

	default:
		break;
	}
}

// ニュートラル位置に戻す(マニュアル操作との繋ぎ)
void AutomaticCamera::ReturnNeutral(const Fighter* p_player_fighter, const Automatic* p_player_automatic, PhysicsColliderSphere* p_player_pc, const Transform* p_player_tr)
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
	fixation_pos = VAdd(VScale(fixation_pos, p_player_fighter->cameraFixationOffset), fighter_pos);

	//VECTOR target_pos = VAdd(fighter_pos, VNorm(VGet(-fighter_forward.x, 0, -fighter_forward.z)));
	VECTOR target_pos = VNorm(VGet(-fighter_forward.x, 0, -fighter_forward.z));

	// カメラをロドリゲスの回転公式で自機正面が見えるよう位置調整
	VECTOR axis = p_player_pc->GetDirection(VGet(1.0f, 0.0f, 0.0f));
	float rad = ((-p_player_fighter->cameraDefaultPitchAngle)) * DX_PI_F / 180.0f;
	float c = std::cos(rad);
	float s = std::sin(rad);
	target_pos = VAdd(VScale(target_pos, c), VScale(VCross(axis, target_pos), s));

	axis = VGet(0.0f, 1.0f, 0.0f);
	rad = 0.0f;
	c = std::cos(rad);
	s = std::sin(rad);
	target_pos = VAdd(VScale(target_pos, c), VScale(VCross(axis, target_pos), s));

	target_pos = VAdd(VScale(target_pos, p_player_fighter->cameraDistance), fixation_pos);

	//camera_pos = VAdd(camera_pos, VScale(VAdd(target_pos, VScale(camera_pos, -1.0f)), std::abs(p_player_automatic->GetCurrentTurnValue())));

	VECTOR vec = VScale(VNorm(VAdd(target_pos, VScale(camera_pos, -1.0f))), 18.0f);
	camera_pos = VAdd(camera_pos, vec);
	//printfDx("%f, %f, %f\n", vec.x, vec.y, vec.z);

	camera->SetPosition(camera_pos);
	camera->SetTarget(fighter_pos);
}

// ピッチターン時のカメラ制御
void AutomaticCamera::PitchTurn(const Fighter* p_player_fighter, const Automatic* p_player_automatic, const Transform* p_player_tr)
{
	// カメラコンポーネントと座標の取得
	Camera* camera = m_owner->GetComponent<Camera>();
	VECTOR camera_pos = camera->GetPosition();

	// 視野角設定
	camera->SetFOV(60);

	// 自機の座標の取得
	VECTOR fighter_pos = p_player_tr->GetPosition();

	// カメラ設定
	camera->SetPosition(VGet(camera_pos.x, fighter_pos.y, camera_pos.z));
	camera->SetTarget(fighter_pos);
	camera->SetDispCenter(Screen::Width / 2, (Screen::Height / 2));
}
