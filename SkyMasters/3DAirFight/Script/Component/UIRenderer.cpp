#include "UIRenderer.h"
#include"Transform.h"
#include"../Actor/Actor.h"


UIRenderer::~UIRenderer() {}

void UIRenderer::SetGrphHandle(int handle)
{
	m_graphHandle = handle;
}

// XV
void UIRenderer::Update()
{
	if (m_isVisible)
	{
		Draw();
	}
}

// ‰æ‘œ‚Ì•`‰æ
void UIRenderer::Draw()
{
	if (m_graphHandle == -1)
	{
		return;
	}

	Transform* tr = m_owner->GetComponent<Transform>();

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

	GetGraphSize(m_graphHandle, &sizeXBuf, &sizeYBuf);

	DrawRotaGraph3(pos.x, pos.y, sizeXBuf / 2, sizeYBuf / 2, scale.x, scale.y, angle, m_graphHandle, TRUE, FALSE);
	
}