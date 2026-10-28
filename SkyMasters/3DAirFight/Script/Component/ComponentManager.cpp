// ライブラリ・ヘッダ
#include "ComponentManager.h"
#include "Component.h"

// コンポーネントの追加
void ComponentManager::AddComponent(Component* component)
{
	//ソート済みベクター内で挿入位置を見つける
	//（自分より順序が高い最初の要素）
	int myOrder = component->GetUpdateOrder();
	auto iter = p_components.begin();
	for (; iter != p_components.end(); ++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	// イテレーターの位置の前に要素を挿入する
	p_components.insert(iter, component);
}

// コンポーネントの削除
void ComponentManager::RemoveComponent(Component* component)
{
	auto iter = std::find(p_components.begin(), p_components.end(), component);
	if (iter != p_components.end())
	{
		p_components.erase(iter);
	}
}

// コンポーネントの更新
// アクターは関係なくコンポーネントの更新順にのっとって更新
void ComponentManager::Update()
{
	for (auto comp : p_components)
	{
		comp->Update();
	}
}
