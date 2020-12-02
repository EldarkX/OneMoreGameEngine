#include "Modules/ObjectModule/Object/Actor/Actor.h"

#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/CollisionComponent.h"

#include <algorithm>

Actor::Actor(GameEngine* gameEngine, string ObjectName)
	: Object(ObjectName), mGameEngine(gameEngine)
{
	mTransformComponent = AddComponent<Transform2DComponent>();
}


void Actor::Tick(float deltaTime)
{
	for (auto Comp : mComponents)
	{
		Comp->Tick(deltaTime);
	}
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
	{
		RemoveComponent(mComponents.back());
	}

	Object::Destroy();
}

void Actor::BeginPlay()
{

}
