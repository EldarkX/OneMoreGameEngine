#pragma once

class Vector2D
{

public:

    Vector2D() = default;

    Vector2D(float x, float y);

    Vector2D(const Vector2D & Vector) = default;

	Vector2D(Vector2D&& Vector) = default;

	Vector2D operator=(const Vector2D& Vector);

	Vector2D &operator+=(const Vector2D& Vector);
	Vector2D &operator-=(const Vector2D& Vector);
	Vector2D &operator*=(const Vector2D& Vector);
	Vector2D &operator/=(const Vector2D& Vector);

    virtual float Size() const;

	inline float&X() { return x_; }
	inline float X() const { return x_; } 

	inline float&Y() { return y_; }
	inline float Y() const { return y_; }

protected:

    float x_ = 0;
    float y_ = 0;

};

inline Vector2D operator/(const Vector2D& v, float scalar)
{
	float reversedScalar = 1 / scalar;
	return (Vector2D(v.X() * reversedScalar, v.Y() * reversedScalar));
}

inline Vector2D operator*(const Vector2D &v, float scalar) { return (Vector2D(v.X() * scalar, v.Y() * scalar)); }
inline Vector2D operator+(const Vector2D& v1, const Vector2D& v2) { return (Vector2D(v1.X() + v2.X(), v1.Y() + v2.Y())); }
inline Vector2D operator-(const Vector2D& v1, const Vector2D& v2) { return (Vector2D(v1.X() - v2.X(), v1.Y() - v2.Y())); }
inline Vector2D operator-(const Vector2D& Vector) { return Vector2D(-Vector.X(), -Vector.Y()); }
inline Vector2D Normalize(const Vector2D& Vector) { return (Vector / Vector.Size()); }
