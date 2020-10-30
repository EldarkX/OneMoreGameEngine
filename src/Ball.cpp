#include "../inc/Ball.h"
#include "../inc/Vector2D.h"

Ball::Ball(SDL_Texture* texture,
	Vector2D initialPosition, string ObjectName, Vector2D customSize)
	: MoveableObject(texture, initialPosition, ObjectName, customSize)
{
	_speed = 250;
}

void Ball::OnCollision(class Object* AnotherObject, class Vector2D& point)
{
	if (AnotherObject->GetCollisionType() == ECollisionType::CTE_Player)
	{
		Vector2D BallCenter = GetPosition() + GetSize() / 2;
		Vector2D PlayerCenter = AnotherObject->GetPosition() + GetSize() / 2;

		SetVelocity(Vector2D((BallCenter - PlayerCenter).X() / (AnotherObject->GetSize().X() / 2) - 1, -1));	
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
		bool VerticalReflect = (GetPosition().X() - AnotherObject->GetPosition().X()) > (GetPosition().Y() - AnotherObject->GetPosition().Y());
		if (VerticalReflect)
			SetVelocity(Vector2D(GetVelocity().X() * -1, GetVelocity().Y()));
		else
			SetVelocity(Vector2D(GetVelocity().X(), GetVelocity().Y() * -1));
	}

	SetPosition(GetPosition() + GetVelocity());

	if (AnotherObject->GetCollisionType() == ECollisionType::CTE_Block)
	{
		AnotherObject->isPendingToKill = true;
	}
}

void Ball::Movement()
{
	MoveableObject::Movement();

	if (GetPosition().Y() >= Game::GetInstance()->GetWindowHeight())
	{
		Game::GetInstance()->gameStatus = EGameStatus::GSE_Exit;
	}
}
