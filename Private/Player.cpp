#include "Player.h"

void Player::OnCollision(class Actor* AnotherObject, class Vector2D& point)
{
	
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

