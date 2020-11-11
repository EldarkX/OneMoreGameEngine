#pragma once

#include "Modules/ObjectModule/Object/Actor/Actor.h"

class Player : public Actor
{

public:

	Player(class GameEngine* gameEngine, string ObjectName);

	class SpriteComponent*		Sprite;
	class CollisionComponent*	Collision;

protected:
	virtual void				Movement(float deltaTime) override;

};