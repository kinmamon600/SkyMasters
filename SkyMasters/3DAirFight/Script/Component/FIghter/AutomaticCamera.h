#ifndef _AUTOMATICCAMERA_H
#define _AUTOMATICCAMERA_H

// ライブラリ・ヘッダ
#include "../Component.h"
#include "../ComponentUpdateOrder.h"

// 前方宣言
class Fighter;
class Transform;
class Automatic;
class PhysicsColliderSphere;

class AutomaticCamera : public Component
{
public:
	// コンストラクタ
	AutomaticCamera(Actor* owner)
		: Component(owner, static_cast<int>(ComponentUpdateOrder::Behaviour)) {}

	// デストラクタ
	~AutomaticCamera() {}

	// ターン時のカメラ制御
	void TurnCamera(const Fighter* p_player_fighter, const Automatic* p_player_automatic, PhysicsColliderSphere* p_player_pc, const Transform* p_player_tr);

private:
	// ニュートラル位置に戻す(マニュアル操作との繋ぎ)
	void ReturnNeutral(const Fighter* p_player_fighter, const Automatic* p_player_automatic, PhysicsColliderSphere* p_player_pc, const Transform* p_player_tr);

	// ピッチターン時のカメラ制御
	void PitchTurn(const Fighter* p_player_fighter, const Automatic* p_player_automatic, const Transform* p_player_tr);
};

#endif