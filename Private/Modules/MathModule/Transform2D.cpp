#include "Modules/MathModule/Transform2D.h"

Transform2D::Transform2D(Vector2D position, Vector2D size, float rotationAngle)
	: mPosition(position), mSize(size), mRotationAngle(rotationAngle)
{

}

void Transform2D::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

void Transform2D::SetSize(Vector2D newSize)
{
	mSize = newSize;
}

void Transform2D::SetAngle(float newRotationAngle)
{
	mRotationAngle = newRotationAngle;
}

