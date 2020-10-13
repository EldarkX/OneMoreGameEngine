
#include "../inc/vec2d.h"

#include <cmath>

Vec2D::Vec2D() : _x(0),  _y(0) {};

Vec2D::Vec2D(double v) : _x(v), _y(v) {};

Vec2D::Vec2D(double x, double y) : _x(x), _y(y) {};

Vec2D::Vec2D(const Vec2D &v) : _x(v.X()), _y(v.Y()) {};

double &Vec2D::X() { return _x;};

double &Vec2D::Y() { return _y;};

double Vec2D::Size()
{
    return (sqrt(pow(_x, 2) + pow(_y, 2)));
}

Vec2D operator*(const Vec2D &v, float scalar)
{
    return (Vec2D(v.X() * scalar, v.Y() * scalar));
}

Vec2D operator+(const Vec2D &v1, const Vec2D &v2)
{
    return (Vec2D(v1.X() + v2.X(), v1.Y() + v2.Y()));
}
