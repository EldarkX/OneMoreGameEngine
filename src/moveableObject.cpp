#include "../inc/moveableObject.h"

MoveableObject::MoveableObject(SDL_Texture *texture, 
        Vector2D initialPosition, string ObjectName, Vector2D customSize)
        : Object(texture, initialPosition, ObjectName, customSize)
{
    _speed = 270;
}

void MoveableObject::Tick()
{
	Object::Tick();

    Movement();
}

void MoveableObject::SetSpeed(float newSpeed)
{
	_speed = newSpeed;
}

void MoveableObject::Movement()
{
    SetPosition(GetPosition() +
        Vector2D(_velocity * _speed * Game::DeltaTime));
}