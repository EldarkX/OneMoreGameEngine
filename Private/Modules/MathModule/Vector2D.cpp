
#include "Modules/MathModule/Vector2D.h"

#include <cmath>

Vector2D::Vector2D(float x, float y) : x_(x), y_(y) {};

Vector2D& Vector2D::operator+=(const Vector2D& Vector)
{
	x_ += Vector.X();
	y_ += Vector.Y();

	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& Vector)
{
	x_ -= Vector.X();
	y_ -= Vector.Y();

	return *this;
}

Vector2D& Vector2D::operator*=(const Vector2D& Vector)
{
	x_ *= Vector.X();
	y_ *= Vector.Y();

	return *this;
}

Vector2D& Vector2D::operator/=(const Vector2D& Vector)
{
	x_ /= Vector.X();
	y_ /= Vector.Y();

	return *this;
}

Vector2D Vector2D::operator=(const Vector2D& Vector)
{
	x_ = Vector.X();
	y_ = Vector.Y();

	return *this;
}

float Vector2D::Size() const
{
    return (sqrt(pow(x_, 2) + pow(y_, 2)));
}
