#include "Modules/ObjectModule/Object.h"

Object::Object(string ObjectName) : mObjectName(ObjectName)
{

}

void Object::Tick(double deltaTime)
{
	if (mIsPendingToKill)
	{
		Destroy();
	}
}

void Object::Destroy()
{
	delete this;
}