#pragma once

#include "moveableObject.h"

class Ball : public MoveableObject
{
public:

	Ball(SDL_Texture* texture,
		Vector2D initialPosition, string ObjectName, Vector2D customSize);

	virtual void OnCollision(class Object* AnotherObject, class Vector2D& point) override;

protected:

	virtual void Movement() override;

};

