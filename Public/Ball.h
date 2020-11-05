#pragma once

#include "Modules/ObjectModule/Object/Actor/Actor.h"

class Ball : public Actor
{
public:

	Ball(class GameEngine* gameEngine, SDL_Texture* texture,
		Vector2D initialPosition, Vector2D customSize, string ObjectName)
		: Actor(gameEngine, texture, initialPosition, customSize, ObjectName)
	{
		mCollisionType = ECollisionType::CTE_Ball;
		mSpeed = 250;
	};

	virtual void	OnCollision(class Actor* AnotherObject, class Vector2D& point);

protected:

	virtual void	Movement(double deltaTime) override;

};

