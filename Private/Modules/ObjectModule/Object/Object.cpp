#include "Modules/ObjectModule/Object.h"

Object::Object(string ObjectName) : mObjectName(ObjectName)
{

}

void Object::BeginPlay()
{

}

void Object::Tick(float deltaTime)
{

}

void Object::Destroy()
{
	OnDestroyed(this);

	delete this;
}
