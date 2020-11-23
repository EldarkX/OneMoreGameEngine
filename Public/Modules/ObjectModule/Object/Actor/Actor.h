#pragma once

#include "Modules/ObjectModule/Object.h"
#include "Modules/MathModule/Vector2D.h"
#include "Modules/ObjectModule/Object/Actor/Components/Transform2DComponent.h"

#include <algorithm>

class Actor : public Object
{

public:

	Actor(GameEngine* gameEngine, string ObjectName);

	virtual void					BeginPlay() override;

    virtual void					Tick(float deltaTime) override;

	class Transform2DComponent		*GetActorTransform() const { return mTransformComponent; }

	Vector2D						GetActorPosition() const { return mTransformComponent->GetPosition(); }
	Vector2D						GetActorSize() const { return mTransformComponent->GetSize(); }

	void							SetActorPosition(Vector2D newPosition) { mTransformComponent->SetPosition(newPosition); }
	void							SetActorSize(Vector2D newSize) { mTransformComponent->SetSize(newSize); }

	class GameEngine				*GetGameEngine() const { return mGameEngine; }

	bool							GetIsPendingToKill() const { return mIsPendingToKill; }
	void							SetIsPendingToKill(bool newIsPendingToKill);

	vector<class BaseComponent*>	GetComponents() const { return mComponents; }

	MulticastDelegate1<Actor*>		OnStartBeingPendingToKill;

	template<class T>
	T* AddComponent()
	{
		BaseComponent* NewComponent = new T();

		NewComponent->SetOwner(this);

		mComponents.push_back(NewComponent);

		return dynamic_cast<T *>(NewComponent);
	}

	void							RemoveComponent(class BaseComponent* Component);

	virtual void Destroy() override;

protected:

	class GameEngine				*mGameEngine;

	vector<class BaseComponent*>	mComponents;

	class Transform2DComponent		*mTransformComponent;

	bool			mIsPendingToKill = false;

};