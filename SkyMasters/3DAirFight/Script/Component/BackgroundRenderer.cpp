#include"../Actor/Actor.h"
#include"BackgroundRenderer.h"

BackgroundRenderer::~BackgroundRenderer()
{
	DeleteGraph(m_graphHandle);
}

void BackgroundRenderer::Update()
{
	Draw();
}

void BackgroundRenderer::SetGrphHandle(int handle)
{
	m_graphHandle = handle;
}

void BackgroundRenderer::Draw()
{
	if (m_graphHandle == -1)
	{
		return;
	}

	DrawGraph(0,0,m_graphHandle,FALSE);
}