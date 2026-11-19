#pragma once

// ライブラリ・ヘッダ
#include <vector>

#include "ActorLayer.h"

// 前方宣言
class Game;
class Component;
class ComponentManager;

class Actor
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	Actor(Game* game);
	virtual ~Actor();

	// Update
	void Update();
	//void UpdateComponents();
	virtual void UpdateActor();

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	// レイヤーの取得
	ActorLayer GetLayer() const;

	// アクターの設定
	void SetLayer(ActorLayer layer);

	Game* GetGame() { return mGame; }

	// コンポーネント管理クラスの取得
	ComponentManager* GetComponentManager() const;

	// Add/remove components
	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	template <typename T>
	T* GetComponent()
	{
		for (Component* component : mComponents)
		{
			T* result = dynamic_cast<T*>(component);

			if (result != nullptr)
			{
				return result;
			}
		}
		return nullptr;
	}

private:
	State mState;

	std::vector<Component*> mComponents;
	Game* mGame;

	// 自身のレイヤー
	ActorLayer m_layer = ActorLayer::Default;
};
