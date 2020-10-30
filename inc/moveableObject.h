#pragma once

#include "object.h"
#include "Vector2D.h"

class MoveableObject : public Object
{

public:

    MoveableObject(SDL_Texture *texture, 
        Vector2D initialPosition, string ObjectName, Vector2D customSize);

    virtual void		Tick() override;

    float				GetSpeed() const { return _speed; } ;
    void				SetSpeed(float newSpeed);

    inline Vector2D		GetVelocity() const { return _velocity; } ;
	void				SetVelocity(Vector2D newVelocity) {_velocity = newVelocity;};

protected:

    virtual void		Movement();

    float				_speed;
    Vector2D			_velocity;

};