#pragma once

#include "moveableObject.h"

class Ball : public MoveableObject
{
public:

	Ball(SDL_Texture* texture,
		Vec2D initialPosition, string ObjectName, Vec2D customSize);

	virtual void OnCollision(class Object* AnotherObject, class Vec2D& point) override;
};

