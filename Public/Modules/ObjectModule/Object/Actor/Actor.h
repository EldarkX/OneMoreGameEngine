#pragma once

#include "Modules/ObjectModule/Object.h"
#include "Modules/MathModule/Vector2D.h"
#include "Modules/MathModule/Transform2D.h"

#include <algorithm>

class Actor : public Object
{

public:

    Actor(class GameEngine *gameEngine, SDL_Texture *texture, 
        Vector2D initialPosition, Vector2D customSize, string ObjectName);

    virtual void					Tick(double deltaTime) override;

	virtual void					OnCollision(class Actor* AnotherObject, class Vector2D& point);

	Vector2D						GetActorPosition() const { return mTransform->GetPosition(); }
	Vector2D						GetActorSize() const { return mTransform->GetSize(); }

	void							SetActorPosition(Vector2D newPosition) { mTransform->SetPosition(newPosition); }
	void							SetActorSize(Vector2D newSize) { mTransform->SetSize(newSize); }

    float							GetSpeed() const { return mSpeed; }
    void							SetSpeed(float newSpeed);

    inline Vector2D					GetVelocity() const { return mVelocity; }
	void							SetVelocity(Vector2D newVelocity) { mVelocity = newVelocity; }

	ECollisionType					GetCollisionType() const { return mCollisionType; }
	void							SetCollisionType(ECollisionType newCollisionType) { mCollisionType = newCollisionType; }

	class GameEngine				*GetGameEngine() const { return mGameEngine; }

protected:

	virtual void					Movement(double deltaTime);

	ECollisionType					mCollisionType;

	class GameEngine				*mGameEngine;

	vector<class BaseComponent*>	mComponents;

	Transform2D						*mTransform;

	class SpriteComponent			*mSpriteComponent;

    float							mSpeed;
    Vector2D						mVelocity;

};