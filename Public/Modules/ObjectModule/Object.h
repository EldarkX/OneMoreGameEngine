#pragma once

#include "Modules/CoreModule/GameEngine.h"

class Object
{

public:

	Object(string ObjectName = "UNKNOWN");

	virtual void	Tick(double deltaTime);

	string			GetObjectName() const { return mObjectName; }
	void			SetObjectName(string objName) { mObjectName = objName; }

	virtual void	Destroy();

	bool			GetIsPendingToKill() const { return mIsPendingToKill; }
	void			SetIsPendingToKill(bool newIsPendingToKill) { mIsPendingToKill = newIsPendingToKill; }

protected:

	string			mObjectName;

	bool			mIsPendingToKill = false;

};
