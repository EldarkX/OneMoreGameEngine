#include "../inc/Ball.h"
#include "../inc/vec2d.h"

Ball::Ball(SDL_Texture* texture,
	Vec2D initialPosition, string ObjectName, Vec2D customSize)
	: MoveableObject(texture, initialPosition, ObjectName, customSize)
{
	_speed = 100;
}

void Ball::OnCollision(class Object *AnotherObject, class Vec2D& point)
{
	SetVelocity(GetVelocity() * -1);

	SetPosition(GetPosition() + GetVelocity());

	//if (AnotherObject->GetCollisionType() == ECollisionType::CTE_Block)
	//{
	//	Game::GetInstance()->RemoveBlock(AnotherObject);
	//	delete AnotherObject;
	//}

	//cout << "Collision: Ball and " << AnotherObject->GetObjectName() << " Y = " << GetVelocity().Y() << endl;
}
