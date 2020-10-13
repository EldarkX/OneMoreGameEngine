#pragma once

class Vec2D
{

public:

    Vec2D();

    Vec2D(double v);

    Vec2D(double x, double y);

    Vec2D(const Vec2D &v);

    double Size();

    double &X();
    double X() const { return _x; } ;

    double &Y();
    double Y() const { return _y; } ;

private:

    double _x;
    double _y;

};

Vec2D operator*(const Vec2D &v, float scalar);
Vec2D operator+(const Vec2D &v1, const Vec2D &v2);