// ライブラリ・ヘッダ
#include "SuperDxPhysics.h"

#include "Transform.h"
#include "PhysicsCollider.h"
#include "Actor/Actor.h"

// 行列の取得
const MATRIX& Transform::GetMatrix() const
{
	return m_matrix;
}

// 行列のセット
void Transform::SetMatrix(const MATRIX mat)
{
	m_matrix = mat;
}

// 座標の取得
const VECTOR& Transform::GetPosition() const
{
	//return m_position;
	return VGet(m_matrix.m[3][0], m_matrix.m[3][1], m_matrix.m[3][2]);
}

// 座標のセット
void Transform::SetPosition(const VECTOR& pos)
{
	m_matrix.m[3][0] = pos.x;
	m_matrix.m[3][1] = pos.y;
	m_matrix.m[3][2] = pos.z;

	// 物理コライダーがアタッチされていたら座標更新
	PhysicsCollider* pc = m_owner->GetComponent<PhysicsCollider>();
	if (pc == nullptr) { return; }
	SDP::SetPosition(pc->GetID(), pos);
}

// 回転の取得
const VECTOR& Transform::GetRotation() const
{
	//return m_rotation;
	float rotX = 0.0f, rotY = 0.0f, rotZ = 0.0f;

	GetMatrixXYZRotation(&m_matrix, &rotX, &rotY, &rotZ);
	rotX *= 180.0f / DX_PI;
	rotY *= 180.0f / DX_PI;
	rotZ *= 180.0f / DX_PI;
	return VGet(rotX, rotY, rotZ);
}

// 回転のセット
void Transform::SetRotation(const VECTOR& rotation)
{
	m_matrix = CreateTransformMatrix(GetPosition(), rotation, GetScale());

	// 物理コライダーがアタッチされていたら回転更新
	PhysicsCollider* pc = m_owner->GetComponent<PhysicsCollider>();
	if (pc == nullptr) { return; }
	SDP::SetRotate(pc->GetID(), rotation);
}

// サイズの取得
const VECTOR& Transform::GetScale() const
{
	//return m_scale;
	return VGet(
		sqrtf(m_matrix.m[0][0] * m_matrix.m[0][0] +
			m_matrix.m[0][1] * m_matrix.m[0][1] +
			m_matrix.m[0][2] * m_matrix.m[0][2]),

		sqrtf(m_matrix.m[1][0] * m_matrix.m[1][0] +
			m_matrix.m[1][1] * m_matrix.m[1][1] +
			m_matrix.m[1][2] * m_matrix.m[1][2]),

		sqrtf(m_matrix.m[2][0] * m_matrix.m[2][0] +
			m_matrix.m[2][1] * m_matrix.m[2][1] +
			m_matrix.m[2][2] * m_matrix.m[2][2])
	);
}

// サイズのセット
void Transform::SetScale(const VECTOR& scale)
{
	//m_scale = scale;
	m_matrix = CreateTransformMatrix(GetPosition(), GetRotation(), scale);
}

// 行列の作成
MATRIX Transform::CreateTransformMatrix(const VECTOR& position, const VECTOR& rotation, const VECTOR& scale)
{
	// 度数法からラジアンに変換
	VECTOR rad = VScale(rotation, DX_PI_F / 180.0f);

	// 各行列を作成
	MATRIX scale_mat = MGetScale(VGet(scale.x, scale.y, scale.z));
	
	MATRIX rotation_mat;
	CreateRotationXYZMatrix(&rotation_mat, rad.x, rad.y, rad.z);

	MATRIX translation_mat;
	CreateTranslationMatrix(&translation_mat, position.x, position.y, position.z);

	// S → R → T の順で合成
	MATRIX result = MMult(MMult(scale_mat, rotation_mat), translation_mat);

	return result;
}
