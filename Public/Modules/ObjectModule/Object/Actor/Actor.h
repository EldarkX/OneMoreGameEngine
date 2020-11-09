#pragma once

#include "Modules/ObjectModule/Object.h"
#include "Modules/MathModule/Vector2D.h"
#include "Modules/ObjectModule/Object/Actor/Components/Transform2DComponent.h"

#include <algorithm>

class Actor : public Object
{

public:

	Actor(GameEngine* gameEngine, string ObjectName);

    virtual void					Tick(double deltaTime) override;

	Vector2D						GetActorPosition() const { return mTransformComponent->GetPosition(); }
	Vector2D						GetActorSize() const { return mTransformComponent->GetSize(); }

	virtual void					OnCollision(class Actor* AnotherActor, class CollisionComponent* AnotherCollisionComponent);

	void							SetActorPosition(Vector2D newPosition) { mTransformComponent->SetPosition(newPosition); }
	void							SetActorSize(Vector2D newSize) { mTransformComponent->SetSize(newSize); }

    float							GetSpeed() const { return mSpeed; }
    void							SetSpeed(float newSpeed);

    inline Vector2D					GetVelocity() const { return mVelocity; }
	void							SetVelocity(Vector2D newVelocity) { mVelocity = newVelocity; }

	class GameEngine				*GetGameEngine() const { return mGameEngine; }

	template<class T>
	T* AddComponent()
	{
		BaseComponent* NewComponent = new T(this);

		mComponents.push_back(NewComponent);

		return NewComponent;
	}

	void							RemoveComponent(class BaseComponent* Component);


	virtual void Destroy() override;

protected:

	virtual void					Movement(double deltaTime);

	class GameEngine				*mGameEngine;

	vector<class BaseComponent*>	mComponents;

	class Transform2DComponent		*mTransformComponent;

    float							mSpeed;
    Vector2D						mVelocity;

};