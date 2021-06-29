
#include "Modules/MathModule/Vector2D.h"

#include <cmath>

const Vector2D Vector2D::UnitVector(1.f, 1.f);
const Vector2D Vector2D::ZeroVector(0.f, 0.f);

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
