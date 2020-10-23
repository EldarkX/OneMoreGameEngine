#pragma once

#include "object.h"
#include "vec2d.h"

class MoveableObject : public Object
{

public:

    MoveableObject(SDL_Texture *texture, 
        Vec2D initialPosition, string ObjectName, Vec2D customSize);

    virtual void Tick() override;

    float   GetSpeed() const { return _speed; } ;
    void    SetSpeed(float newSpeed);

    inline Vec2D   GetVelocity() const { return _velocity; } ;
	void    SetVelocity(Vec2D newVelocity) {_velocity = newVelocity;};

protected:

    void Movement();

    float _speed;
    Vec2D _velocity;

};