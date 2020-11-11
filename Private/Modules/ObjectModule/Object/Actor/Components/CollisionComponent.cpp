
#include "Modules/ObjectModule/Object/Actor/Components/CollisionComponent.h"

#include "Modules/CoreModule/CollisionManager.h"
#include "Modules/ObjectModule/Object/Actor/Actor.h"

void CollisionComponent::TriggerCollision(class Actor* AnotherActor, CollisionComponent* AnotherCollisionComponent)
{
	OnComponentCollided(AnotherActor, AnotherCollisionComponent);
}

void CollisionComponent::Destroy()
{
	mOwner->GetGameEngine()->GetCollisionManager()->RemoveAgent(this);

	Object::Destroy();
}
