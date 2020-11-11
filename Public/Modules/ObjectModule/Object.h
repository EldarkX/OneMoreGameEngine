#pragma once

#include "Modules/CoreModule/GameEngine.h"

#include "Utils/Delegate/MulticastDelegate.h"

using namespace DelegateLib;

class Object
{

public:

	Object(string ObjectName = "UNKNOWN");

	virtual void	Tick(float deltaTime);

	string			GetObjectName() const { return mObjectName; }
	void			SetObjectName(string objName) { mObjectName = objName; }

	virtual void	Destroy();

	bool			GetIsPendingToKill() const { return mIsPendingToKill; }
	void			SetIsPendingToKill(bool newIsPendingToKill) { mIsPendingToKill = newIsPendingToKill; }

	MulticastDelegate1<Object*> OnDestroyed;

protected:

	string			mObjectName;

	bool			mIsPendingToKill = false;

};
