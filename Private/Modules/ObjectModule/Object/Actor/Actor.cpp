#include "Modules/ObjectModule/Object/Actor/Actor.h"

#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/CollisionComponent.h"

Actor::Actor(GameEngine* gameEngine, string ObjectName)
	: Object(ObjectName), mGameEngine(gameEngine)
{
	mTransformComponent = AddComponent<Transform2DComponent>();
	
    mSpeed = 270;
}


void Actor::Tick(float deltaTime)
{
	for (auto Comp : mComponents)
		Comp->Tick(deltaTime);

	Movement(deltaTime);
}

void Actor::SetSpeed(float newSpeed)
{
	mSpeed = newSpeed;
}

void Actor::RemoveComponent(BaseComponent* Component)
{
	mComponents.erase(find(mComponents.cbegin(), mComponents.cend(), Component));

	Component->Destroy();
}

void Actor::SetIsPendingToKill(bool newIsPendingToKill)
{
	mIsPendingToKill = newIsPendingToKill;

	if (mIsPendingToKill)
	{
		OnStartBeingPendingToKill(this);
	}
}

void Actor::Destroy()
{
	while (!mComponents.empty())
		RemoveComponent(mComponents[0]);

	Object::Destroy();
}

void Actor::Movement(float deltaTime)
{
	mTransformComponent->SetPosition(mTransformComponent->GetPosition() +
        Vector2D(mVelocity * mSpeed * deltaTime));
}