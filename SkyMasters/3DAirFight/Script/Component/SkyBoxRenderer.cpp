#include "SkyboxRenderer.h"

// デストラクタ
SkyboxRenderer::~SkyboxRenderer()
{
    Release();
}

// 更新
void SkyboxRenderer::Update()
{
    Draw();
}

// モデルハンドルの設定
void SkyboxRenderer::SetHandles(int model_handle, int texture_handle)
{
    m_modelHandle = model_handle;
    m_textureHandle = texture_handle;
    MV1SetTextureGraphHandle(m_modelHandle, 0, m_textureHandle, FALSE);
    MV1SetMaterialDifColor(m_modelHandle, 0, GetColorF(0.0f, 0.0f, 0.0f, 1.0f));
    MV1SetMaterialSpcColor(m_modelHandle, 0, GetColorF(0.0f, 0.0f, 0.0f, 1.0f));
    MV1SetMaterialEmiColor(m_modelHandle, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
    MV1SetMaterialAmbColor(m_modelHandle, 0, GetColorF(0.0f, 0.0f, 0.0f, 1.0f));
    MV1SetMaterialSpcPower(m_modelHandle, 0, 0.0f);
}

// テクスチャの設定
void SkyboxRenderer::SetTextureHandle(int texture_handle)
{
    m_textureHandle = texture_handle;
    MV1SetTextureGraphHandle(m_modelHandle, 0, m_textureHandle, FALSE);
}

// カメラの位置に合わせて背景の中心を移動
void SkyboxRenderer::SetCenterPosition(VECTOR position)
{
    m_centerPosition = position;
}

// 球体の大きさを設定
void SkyboxRenderer::SetScale(float scale)
{
    m_scale = scale;
    MV1SetScale(m_modelHandle, VGet(m_scale, m_scale, m_scale));
}

// モデルの描画
void SkyboxRenderer::Draw()
{
    if (m_modelHandle == -1)
    {
        return;
    }
    if (m_textureHandle == -1)
    {
        return;
    }

    // 背景モデルの位置と大きさを設定
    MV1SetPosition(m_modelHandle, m_centerPosition);

    MV1DrawModel(m_modelHandle);
}

// モデルの解放
void SkyboxRenderer::Release()
{
    if (m_modelHandle != -1)
    {
        MV1DeleteModel(m_modelHandle);
        m_modelHandle = -1;
    }
}