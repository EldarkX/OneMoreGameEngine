
#include "Block.h"

#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/CollisionComponent.h"

Block::Block(class GameEngine* gameEngine, string ObjectName)
	: Actor(gameEngine, ObjectName)
{
	Sprite = AddComponent<SpriteComponent>();

	Collision = AddComponent<CollisionComponent>();

}

void Block::OnCollision(class Actor* AnotherActor, CollisionComponent* AnotherCollisionComponent)
{
	mIsPendingToKill = true;
}

