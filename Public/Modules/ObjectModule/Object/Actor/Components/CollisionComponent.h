#pragma once

#include "Modules/ObjectModule/Object/Components/BaseComponent.h"

class CollisionComponent : public BaseComponent
{

public:

	CollisionComponent();

	ECollisionType					GetCollisionType() const { return mCollisionType; }
	void							SetCollisionType(ECollisionType newCollisionType) { mCollisionType = newCollisionType; }

	void							TriggerCollision(class Actor *AnotherActor, CollisionComponent *AnotherCollisionComponent);
	
	virtual void					Destroy() override;

private:

	ECollisionType					mCollisionType;

	class Actor						*mOwner;

};