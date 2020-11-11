#pragma once

#include "Modules/ObjectModule/Object/Actor/Actor.h"

class Block : public Actor
{

public:

	Block(class GameEngine* gameEngine, string ObjectName);

	class SpriteComponent*			Sprite;
	class CollisionComponent*		Collision;

	virtual void OnCollision(class Actor* AnotherActor, class CollisionComponent* AnotherCollisionComponent);

private:

};