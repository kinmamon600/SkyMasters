// ライブラリ・ヘッダ
#include <cmath>

#include "../Camera.h"
#include "ManualCamera.h"
#include "../../Actor/Actor.h"
#include"../../Screen/Screen.h"
#include "../Transform.h"
#include "../PhysicsColliderSphere.h"
#include "../PhysicsColliderBox.h"

// カメラコンポーネントを設定
void ManualCamera::SetCamera(const Transform* p_player_tr, PhysicsColliderSphere* p_player_pc, float x_value, float y_value, float fov)
{
	Camera* camera = m_owner->GetComponent<Camera>();

	camera->SetFOV(fov);

	// 自機の座標と向きの取得
	VECTOR fighter_pos = p_player_tr->GetPosition();
	VECTOR fighter_forward = p_player_pc->GetDirection(VGet(0.0f, 0.0f, -1.0f));

	// 注視点の設定
	VECTOR fixation_pos = VNorm(VGet(fighter_forward.x, 0, fighter_forward.z));
	fixation_pos = VAdd(VScale(fixation_pos, cameraFixationOffset), fighter_pos);
	camera->SetTarget(fixation_pos);

	// カメラ座標の設定
	VECTOR camera_pos = VNorm(VGet(-fighter_forward.x, 0, -fighter_forward.z));

	// カメラをロドリゲスの回転公式で自機正面が見えるよう位置調整
	VECTOR axis = p_player_pc->GetDirection(VGet(1.0f, 0.0f, 0.0f));
	float rad = ((-cameraDefaultPitchAngle * (1.0f - abs(x_value))) + cameraPitchAngle * y_value) * DX_PI_F / 180.0f;
	float c = std::cos(rad);
	float s = std::sin(rad);
	camera_pos = VAdd(VScale(camera_pos, c), VScale(VCross(axis, camera_pos), s));

	axis = VGet(0.0f, 1.0f, 0.0f);
	rad = (cameraYawAngle * -x_value) * DX_PI_F / 180.0f;
	c = std::cos(rad);
	s = std::sin(rad);
	camera_pos = VAdd(VScale(camera_pos, c), VScale(VCross(axis, camera_pos), s));

	camera_pos = VAdd(VScale(camera_pos, cameraDistance - (abs(x_value) * cameraTurnDistanceX + abs(y_value) * cameraTurnDistanceY)), fixation_pos);

	camera->SetPosition(camera_pos);

	camera->SetDispCenter((Screen::Width / 2) + (int)((x_value) * cameraCenterAreaX), (Screen::Height / 2) + (int)((y_value) * cameraCenterAreaY));
}
