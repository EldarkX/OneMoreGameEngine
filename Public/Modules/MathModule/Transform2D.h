#pragma once

#include "Vector2D.h"

class Transform2D
{

public:

	Transform2D(Vector2D position, Vector2D size, float rotationAngle);

	void		SetPosition(Vector2D newPosition);
	void		SetSize(Vector2D newSize);
	void		SetAngle(float newRotationAngle);

	Vector2D	GetPosition() const { return mPosition; }
	Vector2D	GetSize() const { return mSize; }
	float		GetAngle() const { return mRotationAngle; }
		
private:

	Vector2D	mPosition;
	Vector2D	mSize;
	float		mRotationAngle;
};