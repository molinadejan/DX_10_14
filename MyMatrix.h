#pragma once

#include "Global.h"
#include "MyVector3.h"

class MyVector3; 

class MyMatrix
{
public :
	MyMatrix();
	~MyMatrix();

private:

	class MyRow
	{
	private:
		vector<float> vecData;

	public:

		MyRow();
		MyRow(int dimension);

		~MyRow();

		void Resize(int dimension);
		float& operator[] (int index);
	};

	vector<MyRow> vecData;

	bool Equal(float a, float b);

public:

	MyMatrix(int dimension);

	void Print();
	void Resize(int dimension);
	int Dimension();

	static MyMatrix Identity(int dimension);

	MyRow& operator[] (int index);

	bool operator==(MyMatrix& mat);
	bool operator!=(MyMatrix& mat);

	MyMatrix operator+(MyMatrix& mat);
	MyMatrix operator-(MyMatrix& mat);

	MyMatrix operator*(MyMatrix& mat);
	MyMatrix operator*(float f);

	MyMatrix Inverse(float& determinant);
	float Determinant();
	MyMatrix Adjoint();
	MyMatrix Transpose();
	float Cofactor(int row, int col);
	float Minor(int row, int col);

	static MyMatrix Translation(float x, float y, float z);
	static MyMatrix Translation(MyVector3& vec);

	static MyMatrix RotationX(float angle);
	static MyMatrix RotationY(float angle);
	static MyMatrix RotationZ(float angle);

	static MyMatrix View(MyVector3& pos, MyVector3& lookAt, MyVector3& up);
	static MyMatrix Projection(float fovY, float aspect, float nearZ, float farZ);
	static MyMatrix Viewport(float x, float y ,float w, float h, float minz, float max);

};