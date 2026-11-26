#ifndef _MANUALCAMERA_H
#define _MANUALCAMERA_H

// ライブラリ・ヘッダ
#include "../Component.h"
#include "../ComponentUpdateOrder.h"

// 前方宣言
class Fighter;
class Transform;
class PhysicsCollider;

class ManualCamera : public Component
{
public:
	// コンストラクタ
	ManualCamera(Actor* owner)
		: Component(owner, static_cast<int>(ComponentUpdateOrder::Behaviour)) {
	}

	// デストラクタ
	~ManualCamera() {}

	// カメラコンポーネントを設定
	void SetCamera(const Fighter* p_player_fighter, const Transform* p_player_tr, PhysicsCollider* p_player_pc, float x_value, float y_value, float fov);

	// カメラを揺らす
	void ShakingCamera();

private:
	// カメラの揺れのステップ
	unsigned short m_shakingStep = 0;

	// 揺れ(カメラの中心座標のずれ)の値
	short m_shakingX = 0;
	short m_shakingY = 0;

	// カメラの揺れの強さ
	const short m_shakingPower = 15;

	// カメラの揺れるフレーム数
	const short m_shakingFrame = 2;
};

#endif