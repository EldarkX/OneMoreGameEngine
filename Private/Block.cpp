
#include "Block.h"

#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/CollisionComponent.h"

#include "Modules/CoreModule/CollisionManager.h"

Block::Block(class GameEngine* gameEngine, string ObjectName)
	: Actor(gameEngine, ObjectName)
{
	Sprite = AddComponent<SpriteComponent>();

	Collision = AddComponent<CollisionComponent>();

	Collision->OnComponentCollided += MakeDelegate(this, &Block::OnCollision);

	GetGameEngine()->GetCollisionManager()->AddAgent(Collision);

}

void Block::OnCollision(class Actor* AnotherActor, CollisionComponent* AnotherCollisionComponent)
{
	if (AnotherCollisionComponent->GetCollisionType() == ECollisionType::CTE_Ball && Collision->GetCollisionType() != ECollisionType::CTE_Wall)
		mIsPendingToKill = true;
}

