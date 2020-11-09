
#include "Modules/ObjectModule/Object/Actor/Components/CollisionComponent.h"

#include "Modules/CoreModule/CollisionManager.h"
#include "Modules/ObjectModule/Object/Actor/Actor.h"

CollisionComponent::CollisionComponent()
{
	mOwner->GetGameEngine()->GetCollisionManager()->AddAgent(this);
}

void CollisionComponent::TriggerCollision(class Actor* AnotherActor, CollisionComponent* AnotherCollisionComponent)
{
	mOwner->OnCollision(AnotherActor, AnotherCollisionComponent);
}

void CollisionComponent::Destroy()
{
	mOwner->GetGameEngine()->GetCollisionManager()->RemoveAgent(this);
}
