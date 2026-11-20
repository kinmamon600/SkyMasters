#pragma once

// ライブラリ・ヘッダ
#include "DxLib.h"
#include "Component.h"
#include "ComponentUpdateOrder.h"

class Transform : public Component
{
public:
	// コンストラクタ
	Transform(Actor* owner)
		:Component(owner, static_cast<int>(ComponentUpdateOrder::Transform)) {}

	// デストラクタ
	~Transform() {}

	// 行列の取得
	const MATRIX& GetMatrix() const;

	// 行列のセット
	void SetMatrix(const MATRIX mat);

	// 座標の取得
	const VECTOR& GetPosition() const;

	// 座標のセット
	void SetPosition(const VECTOR& pos);

	// 回転の取得
	const VECTOR& GetRotation() const;

	// 回転のセット
	void SetRotation(const VECTOR& rotation);

	// サイズの取得
	const VECTOR& GetScale() const;

	// サイズのセット
	void SetScale(const VECTOR& scale);

private:
	//VECTOR m_position = VGet(0.0f, 0.0f, 0.0f);
	//VECTOR m_rotation = VGet(0.0f, 0.0f, 0.0f);
	//VECTOR m_scale = VGet(1.0f, 1.0f, 1.0f);

	// 行列
	MATRIX m_matrix = MGetIdent();

	// 行列の作成
	MATRIX CreateTransformMatrix(const VECTOR& position, const VECTOR& rotation, const VECTOR& scale);
};