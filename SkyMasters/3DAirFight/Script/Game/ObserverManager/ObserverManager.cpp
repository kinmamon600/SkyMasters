// ライブラリ・ヘッダ
#include "ObserverManager.h"
#include "../../Component/Behavior.h"
#include "EventList.h"

// ビヘイビアの追加
void ObserverManager::AddBehavior(Behavior* behavior)
{
	p_behaviors.push_back(behavior);
}

// ビヘイビアの削除
void ObserverManager::RemoveBehavior(Behavior* behavior)
{
	auto iter = std::find(p_behaviors.begin(), p_behaviors.end(), behavior);
	if (iter != p_behaviors.end())
	{
		p_behaviors.erase(iter);
	}
}

// ビヘイビアに通知する
void ObserverManager::Notify(EventList event)
{
	for (Behavior* behavior : p_behaviors)
	{
		behavior->OnNotify(event);
	}
}
