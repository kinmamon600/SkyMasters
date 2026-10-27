#include "ModelRenderer.h"
#include"Transform.h"
#include"../Actor/Actor.h"


ModelRenderer::~ModelRenderer() {}

void ModelRenderer::SetModelHandle(int handle)
{
	m_modelHandle = handle;
}

void ModelRenderer::Update()
{
	if (m_isVisible)
	{
		Draw();
	}
}

void ModelRenderer::Draw()
{
	if (m_modelHandle == -1)
	{
		return;
	}

	Transform* tr = mOwner->GetComponent<Transform>();

	if (tr == nullptr)
	{
		return;
	}

	VECTOR pos = tr->GetPosition();
	VECTOR rote = tr->GetRotation();
	VECTOR scale = tr->GetScale();

	double angleX = rote.x * DX_PI / 180.0;
	double angleY = rote.y * DX_PI / 180.0;
	double angleZ = rote.z * DX_PI / 180.0;


	MV1SetPosition(m_modelHandle, pos);
	MV1SetRotationXYZ(m_modelHandle, VGet(angleX, angleY, angleZ));

	MV1DrawModel(m_modelHandle);

}