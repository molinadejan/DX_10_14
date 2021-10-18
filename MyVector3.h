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

	void Print();

	bool operator==(const MyVector3& vec);
	bool operator!=(const MyVector3& vec);

	MyVector3 operator+(const MyVector3& vec);
	MyVector3 operator-(const MyVector3& vec);

	MyVector3 operator*(float f);
	MyVector3 operator/(float f);

	static float Dot(const MyVector3& vec1, const MyVector3& vec2);
	static MyVector3 Cross(const MyVector3& vec1, const MyVector3& vec2);

	float Length();
	MyVector3 Normalize();

	static MyVector3 TransformCoord(MyVector3& vec, MyMatrix& mat);  // point
	static MyVector3 TransformNormal(MyVector3& vec, MyMatrix& mat); // vector
};