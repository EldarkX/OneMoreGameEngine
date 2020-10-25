#include "../inc/Ball.h"
#include "../inc/vec2d.h"

Ball::Ball(SDL_Texture* texture,
	Vec2D initialPosition, string ObjectName, Vec2D customSize)
	: MoveableObject(texture, initialPosition, ObjectName, customSize)
{
	_speed = 200;
}

void Ball::OnCollision(class Object* AnotherObject, class Vec2D& point)
{
	if (AnotherObject->GetCollisionType() == ECollisionType::CTE_Player)
	{
		Vec2D BallCenter = GetPosition().X() + GetSize().X() / 2;
		Vec2D PlayerCenter = AnotherObject->GetPosition().X() + GetSize().X() / 2;

		SetVelocity(Vec2D((BallCenter - PlayerCenter).X() / (AnotherObject->GetSize().X() / 2) - 1, -1));	
	}
	else if (AnotherObject->GetCollisionType() == ECollisionType::CTE_Wall)
	{
		if (AnotherObject->GetObjectName() == "Left wall" || AnotherObject->GetObjectName() == "Right wall")
			SetVelocity(Vec2D(GetVelocity().X() * -1, GetVelocity().Y()));
		else
			SetVelocity(Vec2D(GetVelocity().X(), GetVelocity().Y() * -1));
	}
	else
	{
		bool VerticalReflect = (GetPosition().X() - AnotherObject->GetPosition().X()) > (GetPosition().Y() - AnotherObject->GetPosition().Y());
		if (VerticalReflect)
			SetVelocity(Vec2D(GetVelocity().X() * -1, GetVelocity().Y()));
		else
			SetVelocity(Vec2D(GetVelocity().X(), GetVelocity().Y() * -1));
	}

	cout << "Ball velocity (" << GetVelocity().X() << " " << GetVelocity().Y() << endl;

	SetPosition(GetPosition() + GetVelocity());

	if (AnotherObject->GetCollisionType() == ECollisionType::CTE_Block)
	{
		AnotherObject->isPendingToKill = true;
	}	
}
