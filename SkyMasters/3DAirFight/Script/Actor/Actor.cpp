#include "Actor.h"
#include "../Game/Game.h"
#include "../Component/Component.h"
#include <algorithm>
#include"DxLib.h"

Actor::Actor(Game* game)
	:mState(EActive)
	, mGame(game)
{
	mGame->AddActor(this);
	//printfDx("Actorコンストラクタが呼ばれたよ\n");
}

Actor::~Actor()
{
	//printfDx("芥のデストラクタが呼ばれたよ\n");
	mGame->RemoveActor(this);
	// デストラクタがRemoveComponentを呼びループするため削除が必要
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor::Update()
{
	if (mState == EActive)
	{
		//UpdateComponents();
		UpdateActor();
	}
}

//void Actor::UpdateComponents()
//{
//	for (auto comp : mComponents)
//	{
//		comp->Update();
//	}
//}

void Actor::UpdateActor()
{

}

void Actor::AddComponent(Component* component)
{
	mGame->AddComponent(component);

	//ソート済みベクター内で挿入位置を見つける
	//（自分より順序が高い最初の要素）
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (;iter != mComponents.end();++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	// イテレーターの位置の前に要素を挿入する
	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	mGame->RemoveComponent(component);

	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}
