// ライブラリ・ヘッダ
#include"Camera.h"

// 更新処理
void Camera::Update()
{
	// 描画範囲設定
	SetDrawArea(m_dispArea_minX, m_dispArea_minY, m_dispArea_maxX, m_dispArea_maxY);

	// 注視点位置設定
	SetCameraScreenCenter(m_dispCenterX, m_dispCenterY);

	// カメラ座標・ターゲット座標・上方向の設定
	SetCameraPositionAndTargetAndUpVec(m_position, m_target, m_up);
}

// カメラの現在座標の取得
const VECTOR& Camera::GetPosition() const
{
	return m_position;
}

// カメラの現在座標の設定
void Camera::SetPosition(const VECTOR& pos)
{
	m_position = pos;
}

// ターゲット座標の取得
const VECTOR& Camera::GetTarget() const
{
	return m_target;
}

// ターゲット座標の設定
void Camera::SetTarget(const VECTOR& pos)
{
	m_target = pos;
}

// カメラの上方向の取得
const VECTOR& Camera::GetUp() const
{
	return m_up;
}

// カメラの上方向の設定
void Camera::SetUp(const VECTOR& pos)
{
	m_up = pos;
}

// 描画範囲設定
void Camera::SetDispArea(unsigned int min_x, unsigned int min_y, unsigned int max_x, unsigned int max_y)
{
	m_dispArea_minX = min_x;
	m_dispArea_minY = min_y;
	m_dispArea_maxX = max_x;
	m_dispArea_maxY = max_y;
}

// 注視点位置取得
void Camera::GetDispCenter(unsigned int* x, unsigned int* y)
{
	*x = m_dispCenterX;
	*y = m_dispCenterY;
}

// 注視点位置設定
void Camera::SetDispCenter(unsigned int x, unsigned int y)
{
	m_dispCenterX = x;
	m_dispCenterY = y;
}

// 視野角の設定
void Camera::SetFOV(float fov)
{
	m_fov = fov;
	SetupCamera_Perspective((m_fov / 180.0f) * DX_PI_F);
}

// 視野角の取得
float Camera::GetFOV() const
{
	return m_fov;
}

// ワールド座標を画面座標に変換
VECTOR Camera::ConvPos2Disp(VECTOR world_pos)
{
	// カメラ設定
	SetDrawArea(m_dispArea_minX, m_dispArea_minY, m_dispArea_maxX, m_dispArea_maxY);
	SetCameraScreenCenter(m_dispCenterX, m_dispCenterY);
	SetCameraPositionAndTargetAndUpVec(m_position, m_target, m_up);

	// 座標取得
	return ConvWorldPosToScreenPos(world_pos);
}
