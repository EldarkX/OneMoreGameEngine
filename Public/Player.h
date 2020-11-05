#pragma once

#include "Modules/ObjectModule/Object/Actor/Actor.h"

class Player : public Actor
{

public:

	Player(class GameEngine* gameEngine, SDL_Texture* texture,
		Vector2D initialPosition, Vector2D customSize, string ObjectName)
		: Actor(gameEngine, texture, initialPosition, customSize, ObjectName)
	{
		mCollisionType = ECollisionType::CTE_Player;
	};


	virtual void OnCollision(class Actor* AnotherObject, class Vector2D& point) override;

protected:
	virtual void Movement(double deltaTime) override;

};