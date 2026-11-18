#include "../Component/Component.h"
#include "../Actor/Actor.h"
#include"DxLib.h"

// コンストラクタ
Component::Component(Actor* owner, int updateOrder)
	:m_owner(owner)
	, m_updateOrder(updateOrder)
{
	m_owner->AddComponent(this);
	//printfDx("Componentコンストラクタが呼ばれたよ\n");
}

// デストラクタ
Component::~Component()
{
	//printfDx("コンポーネントのデストラクタ呼ばれたよ\n");
	m_owner->RemoveComponent(this);
}

// 更新
void Component::Update()
{

}

// アップデート順の取得
int Component::GetUpdateOrder() const
{
	return m_updateOrder;
}

// 自身がアタッチされているアクターの取得
Actor* Component::GetOwner() const
{
	return m_owner;
}
