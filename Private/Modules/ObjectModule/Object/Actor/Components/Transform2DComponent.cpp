#include "Modules/ObjectModule/Object/Actor/Components/Transform2DComponent.h"
#include <algorithm>

void CTransform2DComponent::BeginPlay()
{
	mTransfromPosition = Matrix4D::OneMatrix();
	mTransfromRotation = Matrix4D::OneMatrix();
	mTransfromScale = Matrix4D::OneMatrix();

	mTransfromPosition[2][2] = 0;

	ComputeTransform();
}

void CTransform2DComponent::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
	ComputeTransform();
}

void CTransform2DComponent::SetScale(Vector2D newScale)
{
	float ScaleX = std::clamp(newScale.X(), 0.1f, 10.f);;
	float ScaleY = std::clamp(newScale.Y(), 0.1f, 10.f);;
	mScale = Vector2D(ScaleX, ScaleY);
	ComputeTransform();
}

void CTransform2DComponent::SetAngle(float newRotationAngle)
{
	mRotationAngle = newRotationAngle;
	ComputeTransform();
}

void CTransform2DComponent::ComputeTransform()
{
	mTransfromPosition[3][0] = mPosition.X();
	mTransfromPosition[3][1] = mPosition.Y();

	float cosA = cos(mRotationAngle);
	float sinA = sin(mRotationAngle);

	mTransfromRotation[0][0] = cosA;
	mTransfromRotation[0][1] = sinA;
	mTransfromRotation[1][0] = -sinA;
	mTransfromRotation[1][1] = cosA;

	mTransfromScale[0][0] = mScale.X();
	mTransfromScale[1][1] = mScale.Y();

	mComputedTransform = mTransfromScale;
	mComputedTransform = mComputedTransform * mTransfromRotation;
	mComputedTransform = mComputedTransform * mTransfromPosition;
}

Matrix4D CTransform2DComponent::GetComputedTransform() const
{
	return mComputedTransform;
}

