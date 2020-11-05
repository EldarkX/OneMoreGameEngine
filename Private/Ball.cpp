#include "Ball.h"
#include "Modules/MathModule/Vector2D.h"

#include "Modules/ObjectModule/Object/Actor/Actor.h"

void Ball::OnCollision(class Actor* AnotherObject, class Vector2D& point)
{
	if (AnotherObject->GetCollisionType() == ECollisionType::CTE_Player)
	{
		SetVelocity(Vector2D((GetActorPosition().X() - AnotherObject->GetActorPosition().X()) / (AnotherObject->GetActorSize().X() / 2), -1));
	}
	else
	{
		double SideRX1 = GetActorPosition().X() + GetActorSize().X() / 2.;
		double SideLX1 = GetActorPosition().X() - GetActorSize().X() / 2.;
		double SideRX2 = AnotherObject->GetActorPosition().X() + AnotherObject->GetActorSize().X() / 2.;
		double SideLX2 = AnotherObject->GetActorPosition().X() - AnotherObject->GetActorSize().X() / 2.;

		cout << "SideRX1 = " << SideRX1 << " SideLX1 = " << SideLX1 << endl;
		cout << "SideRX2 = "<< SideRX2 << " SideLX2 = "	 << SideLX2 << endl;

		if (abs(SideRX1 - SideLX2) < 1 || abs(SideLX1 - SideRX2) < 1)
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
