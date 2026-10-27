#include"Camera.h"
#include"../Actor/Actor.h"


const VECTOR& Camera::GetPosition() const
{
	return mPosition;
}

void Camera::SetPosition(const VECTOR& pos)
{
	mPosition = pos;
}

const VECTOR& Camera::GetRotation() const
{
	return mRotation;
}

void Camera::SetRotation(const VECTOR& rotation)
{
	mRotation = rotation;
}

void Camera::Update()
{
	SetCameraNearFar(camNear, camFar);
	SetCameraPositionAndAngle(mPosition, rotateV, rotateH, rotateT);
}