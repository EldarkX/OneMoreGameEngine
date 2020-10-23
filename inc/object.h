#pragma once

#include "arcanoid.h"
#include "vec2d.h"
#include "collisions.h"

class Object
{

public:

	Object(SDL_Texture *texture, Vec2D initialPosition, string ObjectName);

	Object(SDL_Texture *texture, Vec2D initialPosition, string ObjectName, Vec2D customSize);

	virtual void Tick();

	virtual void OnCollision(class Object* AnotherObject, class Vec2D& point);

	Vec2D GetPosition() const;
	Vec2D GetSize() const;

	void SetPosition(Vec2D newPosition);
	void SetSize(Vec2D newSize);

	Vec2D GetLeftUpCorner() const;
	Vec2D GetRightBottomCorner() const;

	string GetObjectName() const;

	ECollisionType GetCollisionType() const;
	void SetCollisionType(ECollisionType newCollisionType);

	virtual void Destroy();

protected:

	virtual void Render(SDL_Renderer *Renderer);

	void RecalculateCorners();

	Vec2D			_position;
	Vec2D			_size;

	Vec2D			_leftUp;
	Vec2D			_rightBottom;

	ECollisionType	collisionType_;

	SDL_Texture		*_texture;

	string			objectName_;

};
