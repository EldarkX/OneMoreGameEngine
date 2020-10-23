#include "../inc/moveableObject.h"

MoveableObject::MoveableObject(SDL_Texture *texture, 
        Vec2D initialPosition, string ObjectName, Vec2D customSize)
        : Object(texture, initialPosition, ObjectName, customSize)
{
    _speed = 80;
}

void MoveableObject::Tick()
{
    Render(Game::GetRenderer());
    Movement();
}

void MoveableObject::SetSpeed(float newSpeed)
{
	_speed = newSpeed;
}

void MoveableObject::Movement()
{
    SetPosition(GetPosition() +
        Vec2D(_velocity * _speed * Game::DeltaTime));
}