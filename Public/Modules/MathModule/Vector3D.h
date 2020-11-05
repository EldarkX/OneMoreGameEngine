#pragma once

#include "Modules/MathModule/Vector2D.h"

class Vector3D : public Vector2D
{

public:

	Vector3D(float x, float y, float z);

	Vector3D() = default;

	Vector3D(const Vector3D& Vector) = default;

	Vector3D(Vector3D&& Vector) = default;

	inline float& Z() { return z_; }
	inline float X() const { return z_; }

	virtual float Size() const override;

private:

	float z_;

};

