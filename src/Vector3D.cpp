#include "../inc/Vector3D.h"

#include <cmath>

Vector3D::Vector3D(float x, float y, float z) : Vector2D(x, y), z_(z) { }

float Vector3D::Size() const 
{
	return (sqrt(pow(x_, 2) + pow(y_, 2) + pow(z_, 2)));
}
