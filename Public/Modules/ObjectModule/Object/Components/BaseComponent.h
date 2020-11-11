#pragma once

#include "Modules/ObjectModule/Object.h"

class BaseComponent : public Object
{

public:

	BaseComponent(class Actor* Owner) : mOwner(Owner) {};

	virtual void	Tick(float deltaTime) override;

	class Actor		*GetOwner() const { return mOwner; }
	void			SetOwner(class Actor *newOwner) { mOwner = newOwner; }

protected:

	class Actor		*mOwner;

};