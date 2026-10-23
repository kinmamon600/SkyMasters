#pragma once

#include"Component.h"
#include"DxLib.h"

class Transform :public Component
{
public:
	Transform(Actor* owner)
		:Component(owner)
	{

	};
	~Transform() {};

	const VECTOR& GetPosition() const { return mPosition; }
	void SetPosition(const VECTOR& pos) { mPosition = pos; }
	const VECTOR& GetRotation() const { return mRotation; }
	void SetRotation(const VECTOR& rotation) { mRotation = rotation; }
	const VECTOR& GetScale() const { return mScale; }
	void SetScale(const VECTOR& scale) { mScale = scale; }

private:
	VECTOR mPosition = VGet(0.0f, 0.0f, 0.0f);
	VECTOR mRotation = VGet(0.0f, 0.0f, 0.0f);
	VECTOR mScale = VGet(1.0f, 1.0f, 1.0f);
};