#pragma once

// ライブラリ・ヘッダ
#include <DxLib.h>
#include "Component.h"
#include "ComponentUpdateOrder.h"

class ModelRenderer : public Component
{
public:
    ModelRenderer(Actor* owner)
        :Component(owner, static_cast<int>(ComponentUpdateOrder::ModelRenderer))
    {

    }
    ~ModelRenderer();

    void Update()override;

    void SetModelHandle(int handle);

private:
    // 3Dオブジェクトハンドル
    int m_modelHandle = -1;

    // 透明度


    // 表示・非表示フラグ
    bool m_isVisible = true;

    // 画像の描画
    void Draw();
};