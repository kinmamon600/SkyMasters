#include "ModelRenderer.h"
#include"Transform.h"
#include"../Actor/Actor.h"


ModelRenderer::~ModelRenderer() {}

// モデルハンドルのセット
void ModelRenderer::SetModelHandle(int handle)
{
	m_modelHandle = handle;
}

// 更新
void ModelRenderer::Update()
{
	if (m_isVisible)
	{
		Draw();
	}
}

// 画像の描画
void ModelRenderer::Draw()
{
	if (m_modelHandle == -1)
	{
		return;
	}

	Transform* tr = m_owner->GetComponent<Transform>();

	if (tr == nullptr)
	{
		return;
	}

	// Transformの取得
	VECTOR pos = tr->GetPosition();
	VECTOR rote = tr->GetRotation();
	VECTOR scale = tr->GetScale();

	// 度数法から弧度法へ変換
	double angleX = rote.x * DX_PI / 180.0;
	double angleY = rote.y * DX_PI / 180.0;
	double angleZ = rote.z * DX_PI / 180.0;

	// モデルの座標と回転をセット
	MV1SetPosition(m_modelHandle, pos);
	MV1SetRotationXYZ(m_modelHandle, VGet(angleX, angleY, angleZ));

	// モデルの描画
	MV1DrawModel(m_modelHandle);

}