// ライブラリ・ヘッダ
#include "DxLib.h"
#include "ComponentManager.h"
#include "Component.h"
#include "ComponentUpdateOrder.h"

// コンポーネントの追加
void ComponentManager::AddComponent(Component* component)
{
	// ソート済みベクター内で挿入位置を見つける
	//（自分より順序が高い最初の要素）
	int myOrder = component->GetUpdateOrder();

	// レンダリング系コンポーネントであれば専用配列に挿入
	if (myOrder > static_cast<int>(ComponentUpdateOrder::StartRenderComponent) &&
		myOrder < static_cast<int>(ComponentUpdateOrder::EndRenderComponent))
	{
		auto iter = p_renderComponents.begin();
		for (; iter != p_renderComponents.end(); ++iter)
		{
			if (myOrder < (*iter)->GetUpdateOrder())
			{
				break;
			}
		}

		// イテレーターの位置の前に要素を挿入する
		p_renderComponents.insert(iter, component);
		printfDx("描画系コンポーネント追加");
	}
	else
	{
		auto iter = p_processComponents.begin();
		for (; iter != p_processComponents.end(); ++iter)
		{
			if (myOrder < (*iter)->GetUpdateOrder())
			{
				break;
			}
		}

		// イテレーターの位置の前に要素を挿入する
		p_processComponents.insert(iter, component);
		printfDx("描画系じゃないコンポーネント追加");
	}
}

// コンポーネントの削除
void ComponentManager::RemoveComponent(Component* component)
{
	int myOrder = component->GetUpdateOrder();

	if (myOrder > static_cast<int>(ComponentUpdateOrder::StartRenderComponent) &&
		myOrder < static_cast<int>(ComponentUpdateOrder::EndRenderComponent))
	{
		// レンダリング系コンポーネントを検索、見つかったら消去
		auto iter = std::find(p_renderComponents.begin(), p_renderComponents.end(), component);
		if (iter != p_renderComponents.end())
		{
			p_renderComponents.erase(iter);
		}
	}
	else
	{
		// 処理系コンポーネントを検索、見つかったら消去
		auto iter = std::find(p_processComponents.begin(), p_processComponents.end(), component);
		if (iter != p_processComponents.end())
		{
			p_processComponents.erase(iter);
		}
	}
}

// コンポーネントの更新
// アクターは関係なくコンポーネントの更新順にのっとって更新
void ComponentManager::Update()
{
	printfDx("更新！");
	// 全コンポーネントを順次更新
	for (auto comp : p_processComponents)
	{
		comp->Update();

		// もしコンポーネントがカメラなら、レンダリング処理も実行する
		if (comp->GetUpdateOrder() == static_cast<int>(ComponentUpdateOrder::Camera))
		{
			for (auto rend_comp : p_renderComponents)
			{
				rend_comp->Update();
			}
		}
	}
}
