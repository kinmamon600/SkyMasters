#ifndef _BEHAVIOR_H
#define _BEHAVIOR_H

// ライブラリ・ヘッダ
#include <vector>

#include <DxLib.h>
#include "Component.h"
#include "ComponentUpdateOrder.h"

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
	Behavior(Actor* owner)
		:Component(owner, static_cast<int>(ComponentUpdateOrder::Behaviour)) {};

	// デストラクタ
	~Behavior() {};

	// コライダーがアタッチされている時、接触を判定する
	void CheckContact(std::vector<Component*> p_physicsColliders);

protected:
	// コライダーがアタッチされている時、接触時に呼ばれる
	virtual void IsContact(const Actor* other) {};

private:

};

#endif