#pragma once

// ライブラリ・ヘッダ
#include <DxLib.h>
#include "Component.h"
#include "ComponentUpdateOrder.h"

class Transform :public Component
{
public:
	Transform(Actor* owner)
		:Component(owner, static_cast<int>(ComponentUpdateOrder::Transform))
	{

	};
	~Transform() {};

	// 座標の取得
	const VECTOR& GetPosition() const { return m_position; }

	// 座標のセット
	void SetPosition(const VECTOR& pos) { m_position = pos; }

	// 回転の取得
	const VECTOR& GetRotation() const { return m_rotation; }

	// 回転のセット
	void SetRotation(const VECTOR& rotation) { m_rotation = rotation; }

	// サイズの取得
	const VECTOR& GetScale() const { return m_scale; }

	// サイズのセット
	void SetScale(const VECTOR& scale) { m_scale = scale; }

private:
	VECTOR m_position = VGet(0.0f, 0.0f, 0.0f);
	VECTOR m_rotation = VGet(0.0f, 0.0f, 0.0f);
	VECTOR m_scale = VGet(1.0f, 1.0f, 1.0f);
};