#include "SkyboxRenderer.h"
#include <DxLib.h>

SkyboxRenderer::~SkyboxRenderer()
{
    Release();
}

bool SkyboxRenderer::Load(const char* filePath)
{
    // “ñd“Ç‚İ‚İ‚ğ–h~
    Release();

    modelHandle = MV1LoadModel(filePath);

    if (modelHandle == -1)
    {
        return false;
    }

    // ”wŒi‚ÉŒõŒ¹‚Ì‰e‹¿‚ğó‚¯‚³‚¹‚È‚¢
    SetUseLighting(FALSE);

    return true;
}

void SkyboxRenderer::SetCenterPosition(VECTOR position)
{
    centerPosition = position;
}

void SkyboxRenderer::SetScale(float scale)
{
    this->scale = scale;
}

void SkyboxRenderer::Draw()
{
    if (modelHandle == -1)
    {
        return;
    }

    // ”wŒiƒ‚ƒfƒ‹‚ÌˆÊ’u‚Æ‘å‚«‚³‚ğİ’è
    MV1SetPosition(modelHandle, centerPosition);
    MV1SetScale(
        modelHandle,
        VGet(scale, scale, scale)
    );

    MV1DrawModel(modelHandle);
}

void SkyboxRenderer::Release()
{
    if (modelHandle != -1)
    {
        MV1DeleteModel(modelHandle);
        modelHandle = -1;
    }
}