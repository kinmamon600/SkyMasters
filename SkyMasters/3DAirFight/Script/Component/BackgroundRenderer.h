#pragma once

// ライブラリ・ヘッダ
#include <DxLib.h>
#include "Component.h"
#include "ComponentUpdateOrder.h"

class BackgroundRenderer : public Component
{
public:
    // コンストラクタ
    BackgroundRenderer(Actor* owner)
        :Component(owner, static_cast<int>(ComponentUpdateOrder::BackgroundRenderer))
    {
    }

    // デストラクタ
    ~BackgroundRenderer();

    // 更新
    void Update();

    // 画像ハンドルのセット
    void SetGrphHandle(int handle);

private:
    // 画像ハンドル
    int m_graphHandle = -1;

    // 画像の描画
    void Draw();
};