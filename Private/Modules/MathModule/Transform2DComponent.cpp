#include "Modules/ObjectModule/Object/Actor/Components/Transform2DComponent.h"

void Transform2DComponent::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

void Transform2DComponent::SetSize(Vector2D newSize)
{
	mSize = newSize;
}

void Transform2DComponent::SetAngle(float newRotationAngle)
{
	mRotationAngle = newRotationAngle;
}

