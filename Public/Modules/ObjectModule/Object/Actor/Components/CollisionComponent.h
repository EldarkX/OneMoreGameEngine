#pragma once

#include "Modules/ObjectModule/Object/Components/BaseComponent.h"

class CollisionComponent : public BaseComponent
{

public:

	ECollisionType					GetCollisionType() const { return mCollisionType; }
	void							SetCollisionType(ECollisionType newCollisionType) { mCollisionType = newCollisionType; }

	void							TriggerCollision(class Actor *AnotherActor, CollisionComponent *AnotherCollisionComponent);
	
	virtual void					Destroy() override;

	MulticastDelegate2<class Actor*, CollisionComponent*> OnComponentCollided;

private:

	ECollisionType					mCollisionType;

};