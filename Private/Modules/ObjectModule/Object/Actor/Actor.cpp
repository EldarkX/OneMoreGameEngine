#include "Modules/ObjectModule/Object/Actor/Actor.h"

#include "Modules/ObjectModule/Object/Components/BaseComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"

Actor::Actor(GameEngine* gameEngine, SDL_Texture *texture,
        Vector2D initialPosition, Vector2D customSize, string ObjectName)
        : Object(ObjectName), mGameEngine(gameEngine)
{
	mTransform = new Transform2D(initialPosition, customSize, 0);

	mSpriteComponent = new SpriteComponent();

	mSpriteComponent->SetTexture(texture);

	mSpriteComponent->SetOwner(this);
	
	//mComponents.push_back(static_cast<BaseComponent *>(mSpriteComponent));

    mSpeed = 270;
}


void Actor::Tick(double deltaTime)
{
	Object::Tick(deltaTime);

	for (auto Comp : mComponents)
		Comp->Tick(deltaTime);

	if (mSpriteComponent && mSpriteComponent->GetTexture())
		mSpriteComponent->Tick(deltaTime);

	Movement(deltaTime);
}

void Actor::OnCollision(class Actor* AnotherObject, class Vector2D& point)
{

}

void Actor::SetSpeed(float newSpeed)
{
	mSpeed = newSpeed;
}

void Actor::Movement(double deltaTime)
{
	mTransform->SetPosition(mTransform->GetPosition() +
        Vector2D(mVelocity * mSpeed * deltaTime));
}