#pragma once
#include "../Component.h"
#include "../ComponentUpdateOrder.h"

#include <cmath>
#include "DxLib.h"

class Input;
class PhysicsColliderBox;

class Manual : public Component
{
public:
	// コンストラクタ
	Manual(Actor* owner)
		: Component(owner, static_cast<int>(ComponentUpdateOrder::Behaviour)) {}

	// デストラクタ
	~Manual() {}

	void FighterControl();

	// 増加:ratioが0.0でmin、1.0でmaxになる
	float VariableTransition_QuadraticIncrease(float ratio, float min, float max);

	// 減少:ratioが0.0でmax、1.0でminになる
	float VariableTransition_QuadraticDecrease(float ratio, float min, float max);

	// 増減:ratioが0.0でmin、0.5でmax、1.0で再びminになる
	float VariableTransition_QuadraticFluctuation(float ratio, float min, float max);
private:
	// 未定義の定数達
	const unsigned int FPS = 60;				// フレームレート
	const unsigned int JOYSTICK_MAX = 1000;		// スティックの最大値

	// 必要なパラメータ群
	float speed = 1.0f;					// 前に進む速度 ブーストとかエアブレーキのときはコレを変更
	float pitchAngularVelocity = 1.0f;	// ピッチ角速度
	float yawAngularVelocity = 1.0f;	// ヨー角速度
	float yawSlopeAngleMax = 45.0f;		// ヨーの時どのくらい傾くか
	float yawSlopeAngleSpeedMax = 2.0f;	// 傾く角速度の最大値
	float yawSlopeAngleSpeedMin = 2.0f;	// 傾く角速度の最小値

	// 処理用の変数群
	float yawSlopeAngle = 0.0f;			// 現状どのくらい傾いているか

	

};