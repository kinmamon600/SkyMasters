#ifndef _DETECTOR_H
#define _DETECTOR_H

// ライブラリ・ヘッダ
#include <functional>
#include "../Component/Behavior.h"
#include "../Actor/Actor.h"

/// <summary>
/// 検知者
/// </summary>
class Detector : public Behavior
{
public:
	// コンストラクタ
	Detector(Actor* owner, const VECTOR pos, float radius, ActorLayer target, std::function<void(Actor*)> func);

	// デストラクタ
	~Detector() {};

private:
	// 検知対象のレイヤー
	ActorLayer m_targetLayer;

	// 検知時に呼び出される関数のポインタ
	std::function<void(Actor*)> p_func;

	// コライダーがアタッチされている時、接触時に呼ばれる
	void IsContact(Actor* other) override;
};

#endif