#pragma once

#include "arcanoid.h"
#include "Vector2D.h"
#include "collisions.h"

class Object
{

public:

	Object(SDL_Texture *texture, Vector2D initialPosition, string ObjectName);

	Object(SDL_Texture *texture, Vector2D initialPosition, string ObjectName, Vector2D customSize);

	virtual void Tick();

	virtual void OnCollision(class Object* AnotherObject, class Vector2D& point);

	Vector2D GetPosition() const;
	Vector2D GetSize() const;

	void SetPosition(Vector2D newPosition);
	void SetSize(Vector2D newSize);

	Vector2D GetLeftUpCorner() const;
	Vector2D GetRightBottomCorner() const;

	string GetObjectName() const;

	ECollisionType GetCollisionType() const;
	void SetCollisionType(ECollisionType newCollisionType);

	virtual void Destroy();

	bool isPendingToKill = false;

protected:

	virtual void Render(SDL_Renderer *Renderer);

	void RecalculateCorners();

	Vector2D			_position;
	Vector2D			_size;

	Vector2D			_leftUp;
	Vector2D			_rightBottom;

	ECollisionType	collisionType_;

	SDL_Texture		*_texture;

	string			objectName_;

};
