#pragma once

#include "arcanoid.h"
#include "vec2d.h"

class Object
{

public:

	Object(SDL_Texture *texture, Vec2D initialPosition);

	Object(SDL_Texture *texture, Vec2D initialPosition, Vec2D customSize);

	virtual void Tick();

	Vec2D GetPosition() const;
	Vec2D GetSize() const;

	void SetPosition(Vec2D newPosition);
	void SetSize(Vec2D newSize);

protected:

	virtual void Render(SDL_Renderer *Renderer);

	Vec2D			_position;
	Vec2D			_size;
	SDL_Texture		*_texture;

};
