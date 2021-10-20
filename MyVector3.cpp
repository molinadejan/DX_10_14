#include "MyVector3.h"
#include "Global.h"
#include <cmath>

bool MyVector3::Equal(float a, float b)
{
	if (fabsf(a - b) <= EPSILON)
		return true;

	return false;
}

MyVector3::MyVector3()
	: x(0), y(0), z(0) { }

MyVector3::MyVector3(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z) { }

void MyVector3::Print() const
{
	printf("Vector : (%8.2f, %8.2f, %8.2f)\n", x, y, z);
}

bool MyVector3::operator==(const MyVector3 & vec) const
{
	return Equal(x, vec.x) && Equal(y, vec.y) && Equal(z, vec.z);
}

bool MyVector3::operator!=(const MyVector3 & vec) const
{
	return !(*this == vec);
}

MyVector3 MyVector3::operator+(const MyVector3 & vec) const
{
	return {x + vec.x, y + vec.y, z + vec.z};
}

MyVector3 MyVector3::operator-(const MyVector3 & vec) const
{
	return {x - vec.x, y - vec.y, z - vec.z};
}

MyVector3& MyVector3::operator+=(const MyVector3& vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return (*this);
}

MyVector3& MyVector3::operator-=(const MyVector3& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return (*this);
}

MyVector3 MyVector3::operator*(float f) const
{
	return {x * f, y * f, z * f};
}

MyVector3 MyVector3::operator/(float f) const
{
	return {x / f, y / f, z / f};
}

float MyVector3::Dot(const MyVector3 & vec1, const MyVector3 & vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

MyVector3 MyVector3::Cross(const MyVector3 & vec1, const MyVector3 & vec2)
{
	return {
		vec1.y * vec2.z - vec1.z * vec2.y, 
					 vec1.z * vec2.x - vec1.x * vec2.z, 
					 vec1.x * vec2.y - vec1.y * vec2.x
	};
}

float MyVector3::Length() const
{
	return sqrt(x * x + y * y + z * z);
}

MyVector3 MyVector3::Normalize() const
{
	float len = Length();
	return {x / len, y / len, z / len};
}

MyVector3 MyVector3::TransformCoord(MyVector3& vec, MyMatrix& mat)
{
	MyVector3 ret;

	ret.x = vec.x * mat[0][0] + vec.y * mat[1][0] + vec.z * mat[2][0] + 1.0f * mat[3][0];
	ret.y = vec.x * mat[0][1] + vec.y * mat[1][1] + vec.z * mat[2][1] + 1.0f * mat[3][1];
	ret.z = vec.x * mat[0][2] + vec.y * mat[1][2] + vec.z * mat[2][2] + 1.0f * mat[3][2];
	float w = vec.x * mat[0][3] + vec.y * mat[1][3] + vec.z * mat[2][3] + 1.0f * mat[3][3];

	if (!Equal(w, 0.0f))
	{
		ret.x /= w;
		ret.y /= w;
		ret.z /= w;
	}

	return ret;
}

MyVector3 MyVector3::TransformNormal(MyVector3& vec, MyMatrix& mat)
{
	MyVector3 ret;

	ret.x = vec.x * mat[0][0] + vec.y * mat[1][0] + vec.z * mat[2][0];
	ret.y = vec.x * mat[0][1] + vec.y * mat[1][1] + vec.z * mat[2][1];
	ret.z = vec.x * mat[0][2] + vec.y * mat[1][2] + vec.z * mat[2][2];

	return ret;
}
