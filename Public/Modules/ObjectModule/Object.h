#pragma once

#include "Modules/CoreModule/GameEngine.h"

class Object
{

public:

	Object(string ObjectName = "UNKNOWN");

	virtual	void				BeginPlay();

	virtual void				Tick(float deltaTime);

	string						GetObjectName() const { return mObjectName; }
	void						SetObjectName(string objName) { mObjectName = objName; }

	virtual void				Destroy();

	MulticastDelegate1<Object*> OnDestroyed;

protected:

	string						mObjectName;

};
