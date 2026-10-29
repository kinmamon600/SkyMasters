#pragma once

// ライブラリ・ヘッダ
#include <DxLib.h>
#include "Component.h"
#include "ComponentUpdateOrder.h"

class SkyboxRenderer : public Component
{
public:
    SkyboxRenderer(Actor* owner)
        :Component(owner, static_cast<int>(ComponentUpdateOrder::SkyboxRenderer))
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
    void Draw();

    // モデルの解放
    void Release();

private:
    int modelHandle = -1;

    VECTOR centerPosition = VGet(0.0f, 0.0f, 0.0f);
    float scale = 1000.0f;
};