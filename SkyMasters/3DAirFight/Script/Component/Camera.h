#pragma once

#include"Component.h"
#include"DxLib.h"

class Camera :public Component
{
public:
	Camera(Actor* owner)
		:Component(owner)
	{

	};
	~Camera() {};

	void Update()override;

	const VECTOR& GetPosition() const;
	void SetPosition(const VECTOR& pos);
	const VECTOR& GetRotation() const;
	void SetRotation(const VECTOR& rotation);
private:
	// ゲームシーンのカメラ設定値
	float camNear = 15.0f;
	float camFar = 5000.0f;

	VECTOR mPosition = VGet(0.0f, 0.0f, 0.0f);
	VECTOR mRotation = VGet(0.0f, 0.0f, 0.0f);

	float rotateV = 0.0f;
	float rotateH = 0.0f;
	float rotateT = 0.0f;
};