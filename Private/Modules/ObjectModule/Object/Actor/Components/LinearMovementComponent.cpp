
#include "Modules/ObjectModule/Object/Actor/Components/LinearMovementComponent.h"

#include "Modules/ObjectModule/Object/Actor/Actor.h"

void LinearMovementComponent::Tick(float deltaTime)
{
	Movement(deltaTime);
}

void LinearMovementComponent::Movement(float deltaTime)
{
	GetOwner()->SetActorPosition(GetOwner()->GetActorPosition() +
		Vector2D(mVelocity * mSpeed * deltaTime));
}

void LinearMovementComponent::SetSpeed(float newSpeed)
{
	mSpeed = newSpeed;
}

void LinearMovementComponent::SetVelocity(Vector2D newVelocity)
{
	mVelocity = newVelocity;

	mVelocity.X() = std::clamp(mVelocity.X(), -1.f, 1.f);
	mVelocity.Y() = std::clamp(mVelocity.Y(), -1.f, 1.f);
}