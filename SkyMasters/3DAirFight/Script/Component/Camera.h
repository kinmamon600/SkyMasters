#ifndef _CAMERA_H
#define _CAMERA_H

// ライブラリ・ヘッダ
#include <DxLib.h>

#include "Screen/Screen.h"

#include "Component.h"
#include "ComponentUpdateOrder.h"

/// <summary>
/// カメラコンポーネント
/// カメラ位置や描画エリア等を設定する
/// </summary>
class Camera : public Component
{
public:
	// コンストラクタ
	Camera(Actor* owner)
		:Component(owner, static_cast<int>(ComponentUpdateOrder::Camera)) {};

	// デストラクタ
	~Camera() {};

	// 更新処理
	void Update()override;

	// カメラの現在座標の取得
	const VECTOR& GetPosition() const;

	// カメラの現在座標の設定
	void SetPosition(const VECTOR& pos);

	// ターゲット座標の取得
	const VECTOR& GetTarget() const;

	// ターゲット座標の設定
	void SetTarget(const VECTOR& pos);

	// カメラの上方向の取得
	const VECTOR& GetUp() const;

	// カメラの上方向の設定
	void SetUp(const VECTOR& pos);

	// 描画範囲設定
	void SetDispArea(unsigned int min_x, unsigned int min_y, unsigned int max_x, unsigned int max_y);

	// 注視点位置設定
	void SetDispCenter(unsigned int x, unsigned int y);

private:
	// カメラの座標
	VECTOR m_position = VGet(0.0f, 0.0f, 0.0f);

	// ターゲット座標
	VECTOR m_target = VGet(0.0f, 0.0f, 1.0f);

	// カメラの上方向
	VECTOR m_up = VGet(0.0f, 1.0f, 0.0f);

	// 画面上の描画範囲
	unsigned int m_dispArea_minX = 0;
	unsigned int m_dispArea_minY = 0;
	unsigned int m_dispArea_maxX = Screen::Width;
	unsigned int m_dispArea_maxY = Screen::Height;

	// 画面上の注視点位置
	unsigned int m_dispCenterX = Screen::Width / 2;
	unsigned int m_dispCenterY = Screen::Height / 2;
};

#endif