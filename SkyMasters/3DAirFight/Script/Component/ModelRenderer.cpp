#include "ModelRenderer.h"
#include "Transform.h"
#include "../Actor/Actor.h"

// デストラクタ
ModelRenderer::~ModelRenderer()
{
	MV1DeleteModel(m_modelHandle);
}

// 更新
void ModelRenderer::Update()
{
	if (m_isVisible)
	{
		Draw();
	}
}

void ModelRenderer::SetScale(VECTOR scale)
{
	MV1SetScale(m_modelHandle, scale);
}

// 画像の描画
void ModelRenderer::Draw()
{
	if (m_modelHandle == -1)
	{
		return;
	}

	Transform* tr = m_owner->GetComponent<Transform>();

	if (tr == nullptr)
	{
		return;
	}

	// Transformの取得
	VECTOR pos = tr->GetPosition();
	VECTOR rote = tr->GetRotation();
	VECTOR scale = tr->GetScale();

	// 度数法から弧度法へ変換
	double angleX = rote.x * DX_PI / 180.0;
	double angleY = rote.y * DX_PI / 180.0;
	double angleZ = rote.z * DX_PI / 180.0;

	// モデルの座標と回転をセット
	MV1SetPosition(m_modelHandle, pos);
	MV1SetRotationXYZ(m_modelHandle, VGet(angleX, angleY, angleZ));

	// モデルの描画
	MV1DrawModel(m_modelHandle);

	// テクスチャマスクが無ければ描画処理終了
	//if (m_textureMasks.size() < 1) { return; }
	//
	//// テクスチャマスクに合わせて上書き描画
	//for (auto tx_mask : m_textureMasks)
	//{
	//	MV1SetTextureGraphHandle(m_modelHandle, 0, tx_mask.textureHandle, FALSE);
	//	MV1SetMaterialDifColor(m_modelHandle, 0, tx_mask.diffuse);
	//	MV1SetMaterialSpcColor(m_modelHandle, 0, tx_mask.specular);
	//	MV1SetMaterialEmiColor(m_modelHandle, 0, tx_mask.emissive);
	//	MV1SetMaterialAmbColor(m_modelHandle, 0, tx_mask.ambient);
	//	MV1SetMaterialSpcPower(m_modelHandle, 0, tx_mask.specularPower);
	//
	//	MV1DrawModel(m_modelHandle);
	//}
	//
	//// 元のテクスチャとマテリアルに戻す
	//MV1SetTextureGraphHandle(m_modelHandle, 0, m_textureHandle, FALSE);
	//MV1SetMaterialDifColor(m_modelHandle, 0, m_diffuse);
	//MV1SetMaterialSpcColor(m_modelHandle, 0, m_specular);
	//MV1SetMaterialEmiColor(m_modelHandle, 0, m_emissive);
	//MV1SetMaterialAmbColor(m_modelHandle, 0, m_ambient);
	//MV1SetMaterialSpcPower(m_modelHandle, 0, m_specularPower);
}

// モデルハンドルのセット
void ModelRenderer::SetModelHandle(int handle)
{
	m_modelHandle = MV1DuplicateModel(handle);
	m_textureHandle = MV1GetTextureGraphHandle(m_modelHandle, 0);

	m_textureMasks.clear();
}

// ディフューズカラーの設定
void ModelRenderer::SetDiffuse(COLOR_F dif)
{
	m_diffuse = dif;
	MV1SetMaterialDifColor(m_modelHandle, 0, m_diffuse);
}

// スペキュラーカラーの設定
void ModelRenderer::SetSpecular(COLOR_F spc)
{
	m_specular = spc;
	MV1SetMaterialSpcColor(m_modelHandle, 0, m_specular);
}

// エミッシブカラーの設定
void ModelRenderer::SetEmissive(COLOR_F emi)
{
	m_emissive = emi;
	MV1SetMaterialEmiColor(m_modelHandle, 0, m_emissive);
}

// アンビエントカラーの設定
void ModelRenderer::SetAmbient(COLOR_F amb)
{
	m_ambient = amb;
	MV1SetMaterialAmbColor(m_modelHandle, 0, m_ambient);
}

// スペキュラーの強さの設定
void ModelRenderer::SetSpecularPower(float power)
{
	m_specularPower = power;
	MV1SetMaterialSpcPower(m_modelHandle, 0, m_specularPower);
}

// テクスチャマスクの追加
void ModelRenderer::AddTextureMask(TextureMask tx_mask)
{
	m_textureMasks.push_back(tx_mask);
}

// テクスチャマスクの削除
void ModelRenderer::RemoveTextureMask(unsigned short index)
{
	// リスト外を指定していたらリターン
	if (index >= m_textureMasks.size())
	{
		return;
	}

	// 指定要素の削除
	m_textureMasks.erase(m_textureMasks.begin() + index);
}
