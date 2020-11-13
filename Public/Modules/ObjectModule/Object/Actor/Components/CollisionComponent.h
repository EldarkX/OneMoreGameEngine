#pragma once

#include "Modules/ObjectModule/Object/Components/BaseComponent.h"

class CollisionComponent : public BaseComponent
{

public:

	virtual void					BeginPlay() override;

	ECollisionType					GetCollisionType() const { return mCollisionType; }
	void							SetCollisionType(ECollisionType newCollisionType) { mCollisionType = newCollisionType; }

	void							TriggerCollision(class Actor *AnotherActor, CollisionComponent *AnotherCollisionComponent);
	MulticastDelegate2<class Actor*, CollisionComponent*> OnComponentCollided;

	virtual void					Destroy() override;

private:

	ECollisionType					mCollisionType;

};