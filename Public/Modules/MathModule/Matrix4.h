#pragma once

#include <vector>

using std::vector;

class Matrix4D
{

public:

	Matrix4D() = default;

	Matrix4D(const Matrix4D& matrix) = default;

	Matrix4D(Matrix4D&& matrix) = default;

	Matrix4D& operator=(const Matrix4D& matrix) = default;

	Matrix4D(vector<vector<float>> Values);

	static Matrix4D OneMatrix();
	static Matrix4D ZeroMatrix();

	vector<float> &operator[](size_t rowIndex);
	vector<float> operator[](size_t rowIndex) const;

	const float* GetAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&mData[0][0]);
	}

private:

	vector<vector<float>> mData = {
		{0.f, 0.f, 0.f, 0.f},
		{0.f, 0.f, 0.f, 0.f},
		{0.f, 0.f, 0.f, 0.f},
		{0.f, 0.f, 0.f, 0.f},
	};
};

inline Matrix4D operator*(const Matrix4D& m, float scalar);
inline Matrix4D operator*(const Matrix4D& m1, const Matrix4D& m2)
{

	Matrix4D result;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			float num = 0;
			for (int k = 0; k < 4; ++k)
			{
				num += m1[i][k] * m2[k][j];
			}
			result[i][j] = num;
		}
	}
	return result;
}
inline Matrix4D operator+(const Matrix4D& m1, const Matrix4D& m2);
inline Matrix4D operator-(const Matrix4D& m1, const Matrix4D& m2);
inline Matrix4D operator-(const Matrix4D& m);