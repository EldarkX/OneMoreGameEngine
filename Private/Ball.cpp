#include "Ball.h"
#include "Modules/MathModule/Vector2D.h"

#include "Modules/ObjectModule/Object/Actor/Actor.h"

#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/CollisionComponent.h"

#include "Player.h"

#include <algorithm>

Ball::Ball(class GameEngine* gameEngine, string ObjectName)
	: Actor(gameEngine, ObjectName)
{
	Sprite = AddComponent<SpriteComponent>();

	Collision = AddComponent<CollisionComponent>();
	Collision->SetCollisionType(ECollisionType::CTE_Ball);

	int mBallWidth = 16, mBallHeight = 16;

	mTransformComponent->SetPosition(Vector2D(gameEngine->GetWindowWidth() / 2.,
		gameEngine->GetWindowHeight() - gameEngine->GetPlayer()->GetActorSize().Y() - mBallHeight / 2. - 1));
	mTransformComponent->SetSize(Vector2D(mBallWidth, mBallHeight));

	mSpeed = 250;

	SetVelocity(Vector2D(0, -1));
};

void Ball::OnCollision(Actor* AnotherActor, CollisionComponent* AnotherCollisionComponent)
{
	if (AnotherCollisionComponent->GetCollisionType() == ECollisionType::CTE_Player)
	{
		SetVelocity(Vector2D((GetActorPosition().X() - AnotherActor->GetActorPosition().X()) / (AnotherActor->GetActorSize().X() / 2), -1));
	}
	else
	{
		double HalfSizeX = GetActorSize().X() / 2.;
		double HalfSizeY = GetActorSize().Y() / 2.;
		double AnotherObjHalfSizeX = AnotherActor->GetActorSize().X() / 2.;
		double AnotherObjHalfSizeY = AnotherActor->GetActorSize().Y() / 2.;

		double minX = std::min(abs(GetActorPosition().X() + HalfSizeX - AnotherActor->GetActorPosition().X() + AnotherObjHalfSizeX),
			abs(GetActorPosition().X() - HalfSizeX - AnotherActor->GetActorPosition().X() - AnotherObjHalfSizeX));

		double minY = std::min(abs(GetActorPosition().Y() + HalfSizeY - AnotherActor->GetActorPosition().Y() + AnotherObjHalfSizeY),
			abs(GetActorPosition().Y() - HalfSizeY - AnotherActor->GetActorPosition().Y() - AnotherObjHalfSizeY));

		if (abs(minX - minY) < 1.)
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

	mTransformComponent->SetPosition(mTransformComponent->GetPosition() + Vector2D(mVelocity));

}

void Ball::Movement(double deltaTime)
{
	Actor::Movement(deltaTime);

	if (mTransformComponent->GetPosition().Y() >= mGameEngine->GetWindowHeight())
	{
		mGameEngine->SetGameStatus(EGameStatus::GSE_Exit);
	}
}
