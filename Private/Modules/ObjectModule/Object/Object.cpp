#include "Modules/ObjectModule/Object.h"

Object::Object(string ObjectName) : mObjectName(ObjectName)
{

}

void Object::Tick(double deltaTime)
{

}

void Object::Destroy()
{
	delete this;
}