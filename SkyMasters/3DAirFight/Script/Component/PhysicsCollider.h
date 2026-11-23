#ifndef _PHYSICSCOLLIDER_H
#define _PHYSICSCOLLIDER_H

// ライブラリ・ヘッダ
#include <DxLib.h>
#include "Component.h"
#include "ComponentUpdateOrder.h"

/// <summary>
/// 物理コライダーコンポーネント
/// コンポーネントの派生クラス且つ、様々な形状の物理コライダーの基底クラス
/// </summary>
class PhysicsCollider : public Component
{
public:
	// コンストラクタ
	PhysicsCollider(Actor* owner);

	// デストラクタ
	~PhysicsCollider();

	// 動作タイプ
	enum MotionType
	{
		Fixed		= 0,
		Active		= 1,
		Keyframe	= 2,
		OneWay		= 3,
		Trigger		= 4,
	};

	// 更新処理
	void Update()override;

	// 座標取得
	VECTOR GetPosition();

	// 回転取得
	VECTOR GetRotate();

	// 向き取得
	VECTOR GetDirection(const VECTOR& std_vec);

	// 速度設定
	void SetLinerVelocity(const VECTOR& vec);

	// 角速度設定
	void SetAngularVelocity(const VECTOR& vec);

	// 回転移動
	float MoveRotate(const VECTOR& rote, float time_step);

	// 速度取得
	VECTOR GetLinerVelocity();
	VECTOR GetAngularVelocity();

	// 質量・逆質量設定
	void SetMass(float mass);
	void SetMassInv(float inv_mass);

	// 質量・逆質量取得
	float GetMass();
	float GetMassInv();

	// 摩擦設定
	void SetFriction(float fric);

	// 摩擦取得
	float GetFriction();

	// 反発係数設定
	void SetRestitution(float elastic);

	// 反発係数取得
	float GetRestitution();

	// SDP上のオブジェクトIDの取得
	int GetID() const;

protected:
	// SDP上のオブジェクトID
	int m_sdpID = -1;

	// トランスフォームの設定(初期設定用)
	void SetTransform();
};

#endif
