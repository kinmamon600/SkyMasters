#pragma once

// ライブラリ・ヘッダ
#include <DxLib.h>
#include "Component.h"
#include "ComponentUpdateOrder.h"

class SkyboxRenderer : public Component
{
public:
    // コンストラクタ
    SkyboxRenderer(Actor* owner)
        :Component(owner, static_cast<int>(ComponentUpdateOrder::SkyboxRenderer)){}

    // デストラクタ
    ~SkyboxRenderer() override;

    // 更新
    void Update() override;

    // モデルハンドルの設定
    void SetHandles(int model_handle, int texture_handle);

    // テクスチャの設定
    void SetTextureHandle(int texture_handle);

    // カメラの位置に合わせて背景の中心を移動
    void SetCenterPosition(VECTOR position);

    // 球体の大きさを設定
    void SetScale(float scale);

    // モデルの描画
    void Draw();

    // モデルの解放
    void Release();

private:
    // 天球のモデルハンドル
    int m_modelHandle = -1;

    // テクスチャのハンドル
    int m_textureHandle = -1;

    VECTOR m_centerPosition = VGet(0.0f, 0.0f, 0.0f);
    float m_scale = 1000.0f;
};