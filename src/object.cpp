#include "../inc/object.h"
#include "../inc/Vector2D.h"
#include "../inc/GameEngine.h"

#include <iostream>

Object::Object(SDL_Texture *texture, Vector2D initialPosition, string ObjectName)
    : _position(initialPosition), _texture(texture)
{
	int w, h;
			
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	_size.X() = w;
	_size.Y() = h;

	collisionType_ = ECollisionType::CTE_Wall;

	objectName_ = ObjectName;

    RecalculateCorners();
};

Object::Object(SDL_Texture *texture, Vector2D initialPosition, string ObjectName,
    Vector2D customSize)
    : Object(texture, initialPosition, ObjectName)
{
	_size.X() = customSize.X();
	_size.Y() = customSize.Y();

	RecalculateCorners();
};

void Object::Tick()
{
	if (isPendingToKill)
	{
		Destroy();
		return;
	}

    Render(Game::GetRenderer());
}

void Object::OnCollision(class Object* AnotherObject, class Vector2D& point)
{

}

void Object::Render(SDL_Renderer *renderer)
{
    SDL_Rect info;

    info.x = _position.X();
    info.y = _position.Y();
    info.w = _size.X();
    info.h = _size.Y();
    
    SDL_RenderCopy(renderer, _texture, NULL, &info);
}

Vector2D Object::GetPosition() const
{
    return _position;
}

Vector2D Object::GetSize() const
{
    return _size;
}

void Object::SetPosition(Vector2D newPosition)
{
    _position.X() = newPosition.X();
    _position.Y() = newPosition.Y();

    RecalculateCorners();
}

void Object::SetSize(Vector2D newSize)
{
    _size.X() = newSize.X();
    _size.Y() = newSize.Y();

    RecalculateCorners();
}

Vector2D Object::GetLeftUpCorner() const
{
	return _leftUp;
}

Vector2D Object::GetRightBottomCorner() const
{
	return _rightBottom;
}

string Object::GetObjectName() const
{
	return objectName_;
}

ECollisionType Object::GetCollisionType() const
{
	return collisionType_;
}

void Object::SetCollisionType(ECollisionType newCollisionType)
{
	collisionType_ = newCollisionType;
}

void Object::Destroy()
{
	if (collisionType_ == ECollisionType::CTE_Block)
		Game::GetInstance()->RemoveBlock(this);

	delete this;
}

void Object::RecalculateCorners()
{
	_leftUp = _position;
    _rightBottom = _position + _size;
}