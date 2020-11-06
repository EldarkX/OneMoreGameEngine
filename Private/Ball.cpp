#include "Ball.h"
#include "Modules/MathModule/Vector2D.h"

#include "Modules/ObjectModule/Object/Actor/Actor.h"

#include <algorithm>

void Ball::OnCollision(class Actor* AnotherObject, class Vector2D& point)
{
	if (AnotherObject->GetCollisionType() == ECollisionType::CTE_Player)
	{
		SetVelocity(Vector2D((GetActorPosition().X() - AnotherObject->GetActorPosition().X()) / (AnotherObject->GetActorSize().X() / 2), -1));
	}
	else
	{
		double minX = std::min(abs(GetActorPosition().X() + GetActorSize().X() / 2.
			- AnotherObject->GetActorPosition().X() + AnotherObject->GetActorSize().X() / 2.),
			abs(GetActorPosition().X() - GetActorSize().X() / 2.
				- AnotherObject->GetActorPosition().X() - AnotherObject->GetActorSize().X() / 2.));

		double minY = std::min(abs(GetActorPosition().Y() + GetActorSize().Y() / 2.
			- AnotherObject->GetActorPosition().Y() + AnotherObject->GetActorSize().Y() / 2.),
			abs(GetActorPosition().Y() - GetActorSize().Y() / 2.
				- AnotherObject->GetActorPosition().Y() - AnotherObject->GetActorSize().Y() / 2.));

		if (abs(minX - minY) < 1)
		{
			SetVelocity(Vector2D(GetVelocity().X() * -1, GetVelocity().Y() * -1));
		}
		if (minX < minY)
		{
			SetVelocity(Vector2D(GetVelocity().X() * -1, GetVelocity().Y()));
		}
		else
		{
			SetVelocity(Vector2D(GetVelocity().X(), GetVelocity().Y() * -1));
		}
	}

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
