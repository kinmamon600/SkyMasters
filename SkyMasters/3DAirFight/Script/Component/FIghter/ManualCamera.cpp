// ライブラリ・ヘッダ
#include <cmath>

#include "../Camera.h"
#include "ManualCamera.h"
#include "../../Actor/Actor.h"
#include"../../Screen/Screen.h"
#include "../Transform.h"
#include "../PhysicsColliderSphere.h"
#include "../PhysicsColliderBox.h"
#include "Fighter.h"

// カメラコンポーネントを設定
void ManualCamera::SetCamera(const Fighter* p_player_fighter, const Transform* p_player_tr, PhysicsCollider* p_player_pc, float x_value, float y_value, float fov)
{
	// カメラコンポーネントの取得
	Camera* camera = m_owner->GetComponent<Camera>();

	// 視野角設定
	camera->SetFOV(fov);

	// 自機の座標と向きの取得
	VECTOR fighter_pos = p_player_tr->GetPosition();
	VECTOR fighter_forward = p_player_pc->GetDirection(VGet(0.0f, 0.0f, -1.0f));

	// 注視点の設定
	VECTOR fixation_pos = VNorm(VGet(fighter_forward.x, 0, fighter_forward.z));
	fixation_pos = VAdd(VScale(fixation_pos, p_player_fighter->m_cameraFixationOffset), fighter_pos);
	camera->SetTarget(fixation_pos);

	// カメラ座標の設定
	VECTOR camera_pos = VNorm(VGet(-fighter_forward.x, 0, -fighter_forward.z));

	// カメラをロドリゲスの回転公式で自機正面が見えるよう位置調整
	VECTOR axis = p_player_pc->GetDirection(VGet(1.0f, 0.0f, 0.0f));
	float rad = ((-p_player_fighter->m_cameraDefaultPitchAngle * (1.0f - abs(y_value))) + p_player_fighter->m_cameraPitchAngle * y_value) * DX_PI_F / 180.0f;
	float c = std::cos(rad);
	float s = std::sin(rad);
	camera_pos = VAdd(VScale(camera_pos, c), VScale(VCross(axis, camera_pos), s));

	axis = VGet(0.0f, 1.0f, 0.0f);
	rad = (p_player_fighter->m_cameraYawAngle * -x_value) * DX_PI_F / 180.0f;
	c = std::cos(rad);
	s = std::sin(rad);
	camera_pos = VAdd(VScale(camera_pos, c), VScale(VCross(axis, camera_pos), s));

	camera_pos = VAdd(VScale(camera_pos, p_player_fighter->m_cameraDistance - (abs(x_value) * p_player_fighter->m_cameraTurnDistanceX + abs(y_value) * p_player_fighter->m_cameraTurnDistanceY)), fixation_pos);

	camera->SetPosition(camera_pos);

	camera->SetDispCenter((p_player_fighter->m_dispCenter.x) + (int)((x_value) * p_player_fighter->m_cameraCenterAreaX), (p_player_fighter->m_dispCenter.y) + (int)((y_value) * p_player_fighter->m_cameraCenterAreaY));
}
