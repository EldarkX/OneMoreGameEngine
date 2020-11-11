#pragma once

#include "Modules/ObjectModule/Object.h"
#include "Modules/MathModule/Vector2D.h"
#include "Modules/ObjectModule/Object/Actor/Components/Transform2DComponent.h"

#include <algorithm>

class Actor : public Object
{

public:

	Actor(GameEngine* gameEngine, string ObjectName);

    virtual void					Tick(float deltaTime) override;

	Vector2D						GetActorPosition() const { return mTransformComponent->GetPosition(); }
	Vector2D						GetActorSize() const { return mTransformComponent->GetSize(); }

	void							SetActorPosition(Vector2D newPosition) { mTransformComponent->SetPosition(newPosition); }
	void							SetActorSize(Vector2D newSize) { mTransformComponent->SetSize(newSize); }

    float							GetSpeed() const { return mSpeed; }
    void							SetSpeed(float newSpeed);

    inline Vector2D					GetVelocity() const { return mVelocity; }
	void							SetVelocity(Vector2D newVelocity) { mVelocity = newVelocity; }

	class GameEngine				*GetGameEngine() const { return mGameEngine; }

	bool							GetIsPendingToKill() const { return mIsPendingToKill; }
	void							SetIsPendingToKill(bool newIsPendingToKill);

	MulticastDelegate1<Actor*>		OnStartBeingPendingToKill;

	template<class T>
	T* AddComponent()
	{
		BaseComponent* NewComponent = new T(this);

		NewComponent->SetOwner(this);

		mComponents.push_back(NewComponent);

		return dynamic_cast<T *>(NewComponent);
	}

	void							RemoveComponent(class BaseComponent* Component);


	virtual void Destroy() override;

protected:

	virtual void					Movement(float deltaTime);

	class GameEngine				*mGameEngine;

	vector<class BaseComponent*>	mComponents;

	class Transform2DComponent		*mTransformComponent;

    float							mSpeed;
    Vector2D						mVelocity;

	bool			mIsPendingToKill = false;

};