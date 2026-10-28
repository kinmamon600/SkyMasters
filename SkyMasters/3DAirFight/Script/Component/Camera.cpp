// ライブラリ・ヘッダ
#include"Camera.h"

// 更新処理
void Camera::Update()
{
	// 描画範囲設定
	// マイナス値(初期値)の時全画面指定
	int area_minx = 0;
	int area_miny = 0;
	int area_maxx = 0;
	int area_maxy = 0;

	if (m_dispArea_minX < 0 || m_dispArea_minY < 0 || m_dispArea_maxX < 0 || m_dispArea_maxY < 0)
	{
		area_minx = 0;
		area_miny = 0;
		GetWindowSize(&area_maxx, &area_maxy);
	}
	else
	{
		area_minx = m_dispArea_minX;
		area_miny = m_dispArea_minY;
		area_maxx = m_dispArea_maxX;
		area_maxy = m_dispArea_maxY;
	}

	SetDrawArea(area_minx, area_miny, area_maxx, area_maxy);

	// 注視点位置設定
	// マイナス値(初期値)の時描画範囲の中心
	if (m_dispCenterX < 0 || m_dispCenterY < 0)
	{
		SetCameraScreenCenter(area_minx + ((area_maxx - area_minx) / 2), area_miny + ((area_maxy - area_miny) / 2));
	}
	else
	{
		SetCameraScreenCenter(m_dispCenterX, m_dispCenterY);
	}

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

// 注視点位置設定
void Camera::SetDispCenter(unsigned int x, unsigned int y)
{
	m_dispCenterX = x;
	m_dispCenterY = y;
}
