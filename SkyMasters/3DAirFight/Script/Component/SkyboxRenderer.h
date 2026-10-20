#pragma once
#include "Component.h"
#include"Dxlib.h"

class SkyboxRenderer : public Component
{
public:
    SkyboxRenderer(Actor* owner)
        :Component(owner)
    {
        
    }
    ~SkyboxRenderer() override;

    // モデルの読み込み
    bool Load(const char* filePath);

    // カメラの位置に合わせて背景の中心を移動
    void SetCenterPosition(VECTOR position);

    // 球体の大きさを設定
    void SetScale(float scale);

    // モデルの描画
    void Draw() override;

    // モデルの解放
    void Release();

private:
    int modelHandle = -1;

    VECTOR centerPosition = VGet(0.0f, 0.0f, 0.0f);
    float scale = 1000.0f;
};