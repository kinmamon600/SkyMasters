#pragma once

// ライブラリ・ヘッダ
#include <vector>

#include "DxLib.h"

#include "Component.h"
#include "ComponentUpdateOrder.h"

class ModelRenderer : public Component
{
public:
    // コンストラクタ
    ModelRenderer(Actor* owner)
        :Component(owner, static_cast<int>(ComponentUpdateOrder::ModelRenderer)){}

    // デストラクタ
    ~ModelRenderer();

    // テクスチャマスクの構造体
    struct TextureMask
    {
        int textureHandle = -1;
        COLOR_F diffuse = GetColorF(0.8f, 0.8f, 0.8f, 1.0f);
        COLOR_F specular = GetColorF(0.2f, 0.2f, 0.2f, 1.0f);
        COLOR_F emissive = GetColorF(0.0f, 0.0f, 0.0f, 1.0f);
        COLOR_F ambient = GetColorF(0.2f, 0.2f, 0.2f, 1.0f);
        float specularPower = 20.0f;
    };

    // 更新
    void Update() override;

    void SetScale(VECTOR scale);

    // モデルハンドルのセット
    void SetModelHandle(int handle);

    // ディフューズカラーの設定
    void SetDiffuse(COLOR_F dif);

    // スペキュラーカラーの設定
    void SetSpecular(COLOR_F spc);

    // エミッシブカラーの設定
    void SetEmissive(COLOR_F emi);

    // アンビエントカラーの設定
    void SetAmbient(COLOR_F amb);

    // スペキュラーの強さの設定
    void SetSpecularPower(float power);

    // テクスチャマスクの追加
    void AddTextureMask(TextureMask tx_mask);

    // テクスチャマスクの削除
    void RemoveTextureMask(unsigned short index);

private:
    // 3Dオブジェクトハンドル
    int m_modelHandle = -1;

    // テクスチャ画像ハンドル
    int m_textureHandle = -1;

    // 表示・非表示フラグ
    bool m_isVisible = true;

    // マテリアルのディフューズカラー(拡散反射色)
    COLOR_F m_diffuse = GetColorF(0.8f, 0.8f, 0.8f, 1.0f);

    // マテリアルのスペキュラーカラー(鏡面反射)
    COLOR_F m_specular = GetColorF(0.2f, 0.2f, 0.2f, 1.0f);

    // マテリアルのエミッシブカラー(自己発光)
    COLOR_F m_emissive = GetColorF(0.5f, 0.5f, 0.5f, 1.0f);

    // マテリアルのアンビエントカラー(環境光)
    COLOR_F m_ambient = GetColorF(0.2f, 0.2f, 0.2f, 1.0f);

    // マテリアルのスペキュラー(鏡面反射)の強さ
    float m_specularPower = 20.0f;

    // 自身のテクスチャマスクリスト
    std::vector<TextureMask> m_textureMasks;

    // 画像の描画
    void Draw();
};