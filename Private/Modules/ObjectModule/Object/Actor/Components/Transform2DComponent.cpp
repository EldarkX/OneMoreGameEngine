#include "Modules/ObjectModule/Object/Actor/Components/Transform2DComponent.h"

void Transform2DComponent::BeginPlay()
{
	mTransfromPosition = Matrix4D::OneMatrix();
	mTransfromRotation = Matrix4D::OneMatrix();
	mTransfromScale = Matrix4D::OneMatrix();

	mTransfromPosition[2][2] = 0;

	ComputeTransform();
}

void Transform2DComponent::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
	ComputeTransform();
}

void Transform2DComponent::SetSize(Vector2D newSize)
{
	mSize = newSize;
	ComputeTransform();
}

void Transform2DComponent::SetAngle(float newRotationAngle)
{
	mRotationAngle = newRotationAngle;
	ComputeTransform();
}

void Transform2DComponent::ComputeTransform()
{
	mTransfromPosition[3][0] = mPosition.X();
	mTransfromPosition[3][1] = mPosition.Y();

	float cosA = cos(mRotationAngle);
	float sinA = sin(mRotationAngle);

	mTransfromRotation[0][0] = cosA;
	mTransfromRotation[0][1] = sinA;
	mTransfromRotation[1][0] = -sinA;
	mTransfromRotation[1][1] = cosA;

	mTransfromScale[0][0] = mSize.X();
	mTransfromScale[1][1] = mSize.Y();

	mComputedTransform = mTransfromScale;
	mComputedTransform = mComputedTransform * mTransfromRotation;
	mComputedTransform = mComputedTransform * mTransfromPosition;
}

Matrix4D Transform2DComponent::GetComputedTransform() const
{
	return mComputedTransform;
}

