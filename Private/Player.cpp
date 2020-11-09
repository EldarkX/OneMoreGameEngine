#include "Player.h"

#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/CollisionComponent.h"

Player::Player(class GameEngine* gameEngine, string ObjectName)
	: Actor(gameEngine, ObjectName)
{
	Sprite = AddComponent<SpriteComponent>();

	Collision = AddComponent<CollisionComponent>();
	Collision->SetCollisionType(ECollisionType::CTE_Player);

	int mPlayerWidth = 80, mPlayerHeight = 10;

	mTransformComponent->SetPosition(Vector2D(gameEngine->GetWindowWidth() / 2, gameEngine->GetWindowHeight() - mPlayerHeight / 2));
	mTransformComponent->SetSize(Vector2D(mPlayerWidth, mPlayerHeight));
}

void Player::Movement(double deltaTime)
{
	Actor::Movement(deltaTime);
	
	double PlayerHalfSizeX = GetActorSize().X() / 2.;

	if (GetActorPosition().X() - PlayerHalfSizeX < 0)
	{
		SetActorPosition(Vector2D(PlayerHalfSizeX, GetActorPosition().Y()));
	}
	else if (GetActorPosition().X() + PlayerHalfSizeX > mGameEngine->GetWindowWidth())
	{
		SetActorPosition(Vector2D(mGameEngine->GetWindowWidth() - PlayerHalfSizeX, GetActorPosition().Y()));
	}

}

