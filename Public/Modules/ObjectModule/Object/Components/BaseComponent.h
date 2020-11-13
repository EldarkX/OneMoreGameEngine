#pragma once

#include "Modules/ObjectModule/Object.h"

class BaseComponent : public Object
{

public:

	virtual void	Tick(float deltaTime) override;

	class Actor		*GetOwner() const { return mOwner; }
	void			SetOwner(class Actor *newOwner) { mOwner = newOwner; }


	virtual void	BeginPlay() override;


	virtual void	Destroy() override;

protected:

	class Actor		*mOwner;

};