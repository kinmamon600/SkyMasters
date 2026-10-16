#pragma once
#include"Component.h"
#include"DxLib.h"

class Transform :public Component
{
public:
	const VECTOR& GetPosition() const { return mPosition; }
	void SetPosition(const VECTOR& pos) { mPosition = pos; }
	const VECTOR& GetRotation() const { return mRotation; }
	void SetRotation(const VECTOR& rotation) { mRotation = rotation; }
	const VECTOR& GetScale() const { return mScale; }
	void SetScale(const VECTOR& scale) { mScale = scale; }

	void Update(float deltaTime);

private:
	VECTOR mPosition;
	VECTOR mRotation;
	VECTOR mScale;
};