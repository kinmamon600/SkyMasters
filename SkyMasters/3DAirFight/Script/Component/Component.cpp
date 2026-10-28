#include "../Component/Component.h"
#include "../Actor/Actor.h"
#include"DxLib.h"

Component::Component(Actor* owner, int updateOrder)
	:mOwner(owner)
	, mUpdateOrder(updateOrder)
{
	mOwner->AddComponent(this);
	printfDx("Componentコンストラクタが呼ばれたよ\n");
}

Component::~Component()
{
	mOwner->RemoveComponent(this);
}

void Component::Update()
{

}

