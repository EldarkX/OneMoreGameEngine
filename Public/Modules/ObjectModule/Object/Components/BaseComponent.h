#pragma once

#include "Modules/ObjectModule/Object.h"

class BaseComponent : public Object
{

public:

	virtual void	Tick(double deltaTime) override;

	class Actor		*GetOwner() const { return mOwner; }
	void			SetOwner(class Actor *newOwner) { mOwner = newOwner; }

protected:

	class Actor		*mOwner = nullptr;

};