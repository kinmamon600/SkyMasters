#ifndef _BEHAVIOR_H
#define _BEHAVIOR_H

// ライブラリ・ヘッダ
#include <vector>

#include <DxLib.h>
#include "Component.h"
#include "ComponentUpdateOrder.h"
#include "../Game/ObserverManager/EventList.h"

// 前方宣言
class Actor;

/// <summary>
/// ビヘイビア
/// UnityのScriptに該当するクラスの基底クラス
/// </summary>
class Behavior : public Component
{
public:
	// コンストラクタ
	Behavior(Actor* owner);

	// デストラクタ
	virtual ~Behavior();

	// コライダーがアタッチされている時、接触を判定する
	void CheckContact(std::vector<Component*> p_physicsColliders);

	// 通知を受け取る
	virtual void OnNotify(EventList event) {};

protected:
	// コライダーがアタッチされている時、接触時に呼ばれる
	virtual void IsContact(Actor* other) {};

	// 通知を送信する
	void Notify(EventList event);

private:

};

#endif