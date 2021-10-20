#pragma once

#include "MyMatrix.h"

class MyMatrix;

class MyVector3
{
private:
	static bool Equal(float a, float b);

public:

	float x, y, z;

	MyVector3();
	MyVector3(float _x, float _y, float _z);

	void Print() const;

	bool operator==(const MyVector3& vec) const;
	bool operator!=(const MyVector3& vec) const;

	MyVector3 operator+(const MyVector3& vec) const;
	MyVector3 operator-(const MyVector3& vec) const;
	MyVector3& operator+=(const MyVector3& vec);
	MyVector3& operator-=(const MyVector3& vec);

	MyVector3 operator*(float f) const;
	MyVector3 operator/(float f) const;

	static float Dot(const MyVector3& vec1, const MyVector3& vec2);
	static MyVector3 Cross(const MyVector3& vec1, const MyVector3& vec2);

	float Length() const;
	MyVector3 Normalize() const;

	static MyVector3 TransformCoord(MyVector3& vec, MyMatrix& mat);  // point
	static MyVector3 TransformNormal(MyVector3& vec, MyMatrix& mat); // vector
};