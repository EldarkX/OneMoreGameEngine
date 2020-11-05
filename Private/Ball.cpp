#include "Ball.h"
#include "Modules/MathModule/Vector2D.h"

#include "Modules/ObjectModule/Object/Actor/Actor.h"

void Ball::OnCollision(class Actor* AnotherObject, class Vector2D& point)
{
	if (AnotherObject->GetCollisionType() == ECollisionType::CTE_Player)
	{
		SetVelocity(Vector2D((mTransform->GetPosition() - AnotherObject->GetActorPosition()).X() / (AnotherObject->GetActorSize().X() / 2) - 1, -1));
	}
	else if (AnotherObject->GetCollisionType() == ECollisionType::CTE_Wall)
	{
		if (AnotherObject->GetObjectName() == "Left wall" || AnotherObject->GetObjectName() == "Right wall")
			SetVelocity(Vector2D(GetVelocity().X() * -1, GetVelocity().Y()));
		else
			SetVelocity(Vector2D(GetVelocity().X(), GetVelocity().Y() * -1));
	}
	else
	{
		bool VerticalReflect = (mTransform->GetPosition().X() - AnotherObject->GetActorPosition().X())
			> (mTransform->GetPosition().Y() - AnotherObject->GetActorPosition().Y());
		if (VerticalReflect)
			SetVelocity(Vector2D(GetVelocity().X() * -1, GetVelocity().Y()));
		else
			SetVelocity(Vector2D(GetVelocity().X(), GetVelocity().Y() * -1));
	}

	mTransform->SetPosition(mTransform->GetPosition() + GetVelocity());

	if (AnotherObject->GetCollisionType() == ECollisionType::CTE_Block)
	{
		AnotherObject->SetIsPendingToKill(true);
	}
}

void Ball::Movement(double deltaTime)
{
	Actor::Movement(deltaTime);

	if (mTransform->GetPosition().Y() >= mGameEngine->GetWindowHeight())
	{
		mGameEngine->SetGameStatus(EGameStatus::GSE_Exit);
	}
}
