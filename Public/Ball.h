#pragma once

#include "Modules/ObjectModule/Object/Actor/Actor.h"

class Ball : public Actor
{
public:

	Ball(class GameEngine* gameEngine, string ObjectName);

	class SpriteComponent*		Sprite;
	class CollisionComponent*	Collision;

	virtual void	OnCollision(class Actor* AnotherActor, class CollisionComponent* AnotherCollisionComponent) override;

protected:

	virtual void	Movement(double deltaTime) override;

};

