#include "SkyboxRenderer.h"

SkyboxRenderer::~SkyboxRenderer()
{
    Release();
}

// ƒ‚ƒfƒ‹‚Ì“Ç‚İ‚İ
bool SkyboxRenderer::Load(const char* filePath)
{
    // “ñd“Ç‚İ‚İ‚ğ–h~
    Release();

    m_modelHandle = MV1LoadModel(filePath);

    if (m_modelHandle == -1)
    {
        return false;
    }

    // ”wŒi‚ÉŒõŒ¹‚Ì‰e‹¿‚ğó‚¯‚³‚¹‚È‚¢
    SetUseLighting(FALSE);

    return true;
}

// ƒJƒƒ‰‚ÌˆÊ’u‚É‡‚í‚¹‚Ä”wŒi‚Ì’†S‚ğˆÚ“®
void SkyboxRenderer::SetCenterPosition(VECTOR position)
{
    m_centerPosition = position;
}

// ‹…‘Ì‚Ì‘å‚«‚³‚ğİ’è
void SkyboxRenderer::SetScale(float scale)
{
    this->m_scale = scale;
}

// ƒ‚ƒfƒ‹‚Ì•`‰æ
void SkyboxRenderer::Draw()
{
    if (m_modelHandle == -1)
    {
        return;
    }

    // ”wŒiƒ‚ƒfƒ‹‚ÌˆÊ’u‚Æ‘å‚«‚³‚ğİ’è
    MV1SetPosition(m_modelHandle, m_centerPosition);
    MV1SetScale(
        m_modelHandle,
        VGet(m_scale, m_scale, m_scale)
    );

    MV1DrawModel(m_modelHandle);
}

// ƒ‚ƒfƒ‹‚Ì‰ğ•ú
void SkyboxRenderer::Release()
{
    if (m_modelHandle != -1)
    {
        MV1DeleteModel(m_modelHandle);
        m_modelHandle = -1;
    }
}