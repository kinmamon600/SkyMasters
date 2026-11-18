#pragma once

// ライブラリ・ヘッダ
#include <DxLib.h>
#include "Component.h"
#include "ComponentUpdateOrder.h"

class UIRenderer : public Component
{
public:
    // コンストラクタ
    UIRenderer(Actor* owner)
        :Component(owner, static_cast<int>(ComponentUpdateOrder::UIRenderer)) 
    {
        //printfDx("UIRendererが呼ばれたよ\n");
    }

    // デストラクタ
    ~UIRenderer();

    // 更新
    void Update();

    // 画像ハンドルのセット
    void SetGrphHandle(int handle);

    void SetIsVisible(bool isVisible);

private:
    // 画像ハンドル
    int m_graphHandle = -1;

    // 透明度
    

    // 表示・非表示フラグ
    bool m_isVisible = true;

    // 画像の描画
    void Draw();
};