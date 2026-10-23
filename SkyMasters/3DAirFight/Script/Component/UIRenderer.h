#pragma once

#include "Component.h"
#include <DxLib.h>

class UIRenderer : public Component
{
public:
    UIRenderer(Actor* owner)
        :Component(owner)
    {

    }
    ~UIRenderer();

    void Update()override;

    void SetGrphHandle(int handle);

private:
    // 画像ハンドル
    int m_graphHandle = -1;

    // 透明度
    

    // 表示・非表示フラグ
    bool m_isVisible = true;

    // 画像の描画
    void Draw();
};