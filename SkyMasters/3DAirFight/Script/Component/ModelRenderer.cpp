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

	double angle = rote.z * DX_PI / 180.0;

	int sizeXBuf = 0;
	int sizeYBuf = 0;

	MV1DrawModel(m_modelHandle);

}