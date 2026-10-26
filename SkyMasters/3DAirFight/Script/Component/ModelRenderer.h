#pragma once

#include "Component.h"
#include <DxLib.h>

class ModelRenderer : public Component
{
public:
    ModelRenderer(Actor* owner)
        :Component(owner)
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