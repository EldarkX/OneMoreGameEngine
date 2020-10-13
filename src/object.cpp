#include "../inc/object.h"
#include "../inc/vec2d.h"
#include "../inc/arcanoid.h"

#include <iostream>

Object::Object(SDL_Texture *texture, Vec2D initialPosition)
    : _position(initialPosition), _texture(texture)
{
	int w, h;
			
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	_size.X() = w;
	_size.Y() = h;
};

Object::Object(SDL_Texture *texture, Vec2D initialPosition,
    Vec2D customSize)
    : Object(texture, initialPosition)
{
	_size.X() = customSize.X();
	_size.Y() = customSize.Y();
};

void Object::Tick()
{
    Render(Game::GetRenderer());
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

Vec2D Object::GetPosition() const
{
    return _position;
}

Vec2D Object::GetSize() const
{
    return _size;
}

void Object::SetPosition(Vec2D newPosition)
{
    _position.X() = newPosition.X();
    _position.Y() = newPosition.Y();
}

void Object::SetSize(Vec2D newSize)
{
    _size.X() = newSize.X();
    _size.Y() = newSize.Y();
}
