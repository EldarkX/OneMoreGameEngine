#include "Modules/ObjectModule/Object/Actor/Actor.h"

#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/CollisionComponent.h"

Actor::Actor(GameEngine* gameEngine, string ObjectName)
	: Object(ObjectName), mGameEngine(gameEngine)
{
	mTransformComponent = AddComponent<Transform2DComponent>();
	
    mSpeed = 270;
}


void Actor::Tick(double deltaTime)
{
	Object::Tick(deltaTime);

	for (auto Comp : mComponents)
		Comp->Tick(deltaTime);

	Movement(deltaTime);
}

void Actor::OnCollision(class Actor* AnotherActor, class CollisionComponent* AnotherCollisionComponent)
{

}

void Actor::SetSpeed(float newSpeed)
{
	mSpeed = newSpeed;
}

//template<class T>
//T *Actor::AddComponent()
//{
//	T* NewComponent = new T();
//
//	NewComponent->SetOwner(this);
//
//	mComponents.push_back(NewComponent);
//
//	return NewComponent;
//}

void Actor::RemoveComponent(BaseComponent* Component)
{
	mComponents.erase(find(mComponents.cbegin(), mComponents.cend(), Component));

	delete Component;
}

void Actor::Destroy()
{
	while (!mComponents.empty())
		RemoveComponent(mComponents[0]);
}

void Actor::Movement(double deltaTime)
{
	mTransformComponent->SetPosition(mTransformComponent->GetPosition() +
        Vector2D(mVelocity * mSpeed * deltaTime));
}