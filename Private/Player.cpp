#include "Player.h"

#include "Modules/ObjectModule/Object/Actor/Components/SpriteComponent.h"
#include "Modules/ObjectModule/Object/Actor/Components/CollisionComponent.h"

#include "Modules/CoreModule/CollisionManager.h"

Player::Player(class GameEngine* gameEngine, string ObjectName)
	: Actor(gameEngine, ObjectName)
{
	Sprite = AddComponent<SpriteComponent>();

	Collision = AddComponent<CollisionComponent>();
	Collision->SetCollisionType(ECollisionType::CTE_Player);

	GetGameEngine()->GetCollisionManager()->AddAgent(Collision);

	float mPlayerWidth = gameEngine->GetWindowWidth() - 20.f, mPlayerHeight = 10.f;

	mTransformComponent->SetPosition(Vector2D(gameEngine->GetWindowWidth() / 2.f, gameEngine->GetWindowHeight() - mPlayerHeight / 2.f));
	mTransformComponent->SetSize(Vector2D(mPlayerWidth, mPlayerHeight));
}

void Player::Movement(float deltaTime)
{
	Actor::Movement(deltaTime);
	
	float PlayerHalfSizeX = GetActorSize().X() / 2.f;

	if (GetActorPosition().X() - PlayerHalfSizeX < 0)
	{
		SetActorPosition(Vector2D(PlayerHalfSizeX, GetActorPosition().Y()));
	}
	else if (GetActorPosition().X() + PlayerHalfSizeX > mGameEngine->GetWindowWidth())
	{
		SetActorPosition(Vector2D(mGameEngine->GetWindowWidth() - PlayerHalfSizeX, GetActorPosition().Y()));
	}

}

