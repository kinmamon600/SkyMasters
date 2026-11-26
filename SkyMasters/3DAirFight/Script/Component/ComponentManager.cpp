// ライブラリ・ヘッダ
#include "DxLib.h"
#include "SuperDxPhysics.h"
#include "ComponentManager.h"
#include "Component.h"
#include "ComponentUpdateOrder.h"
#include "Actor/Actor.h"
#include "Behavior.h"
#include "Screen/Screen.h"

// コンポーネントの追加
void ComponentManager::AddComponent(Component* component)
{
	p_PendingComponents.push_back(component);
}

// コンポーネントの削除
void ComponentManager::RemoveComponent(Component* component)
{
	int myOrder = component->GetUpdateOrder();

	if (myOrder == static_cast<int>(ComponentUpdateOrder::PhysicsCollider))
	{
		// コライダーを検索、見つかったら消去
		auto iter = std::find(p_physicsColliderComponents.begin(), p_physicsColliderComponents.end(), component);
		if (iter != p_physicsColliderComponents.end())
		{
			p_physicsColliderComponents.erase(iter);
		}
	}
	else if (myOrder > static_cast<int>(ComponentUpdateOrder::StartRenderComponent) &&
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
	// 保留状態のアクターを新規登録
	for (auto pending : p_PendingComponents)
	{
		// ソート済みベクター内で挿入位置を見つける
		//（自分より順序が高い最初の要素）
		int myOrder = pending->GetUpdateOrder();

		// コライダー、レンダリング系コンポーネントであれば専用配列に挿入
		if (myOrder == static_cast<int>(ComponentUpdateOrder::PhysicsCollider))
		{
			auto iter = p_physicsColliderComponents.begin();
			for (; iter != p_physicsColliderComponents.end(); ++iter)
			{
				if (myOrder < (*iter)->GetUpdateOrder())
				{
					break;
				}
			}

			// イテレーターの位置の前に要素を挿入する
			p_physicsColliderComponents.insert(iter, pending);
		}
		else if (myOrder > static_cast<int>(ComponentUpdateOrder::StartRenderComponent) &&
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
			p_renderComponents.insert(iter, pending);
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
			p_processComponents.insert(iter, pending);
		}
	}
	p_PendingComponents.clear();

	// 物理演算更新
	SDP::SimulatePhysics();

	// コンポーネントを順次更新
	for (auto comp : p_physicsColliderComponents)
	{
		comp->Update();
	}

	for (auto comp : p_processComponents)
	{
		comp->Update();

		// もしコンポーネントがビヘイビアなら、当たり判定の確認
		if (comp->GetUpdateOrder() == static_cast<int>(ComponentUpdateOrder::Behaviour))
		{
			Behavior* behavior = comp->GetOwner()->GetComponent<Behavior>();

			if (behavior != nullptr)
			{
				behavior->CheckContact(p_physicsColliderComponents);
			}
		}

		// もしコンポーネントがカメラなら、レンダリング処理も実行する
		if (comp->GetUpdateOrder() == static_cast<int>(ComponentUpdateOrder::Camera))
		{
			for (auto rend_comp : p_renderComponents)
			{
				rend_comp->Update();
			}

			// 物理オブジェクトの描画(デバッグ用)
			//SDP::RenderPhysicalObject();

			// 描画範囲初期化
			SetDrawArea(0, 0, Screen::Width, Screen::Height);

			// 注視点位置初期化
			SetCameraScreenCenter(Screen::Width / 2.0f, Screen::Height / 2.0f);
		}
	}
}

// 可変長配列をすべて空に
void ComponentManager::ClearComponents()
{
	p_physicsColliderComponents.clear();
	p_processComponents.clear();
	p_renderComponents.clear();
}