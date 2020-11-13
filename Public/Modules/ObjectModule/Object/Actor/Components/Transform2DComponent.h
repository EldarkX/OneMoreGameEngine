#pragma once

#include "Modules/MathModule/Vector2D.h"
#include "Modules/ObjectModule/Object/Components/BaseComponent.h"

class Transform2DComponent : public BaseComponent
{

public:

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