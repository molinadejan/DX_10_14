#include "MyMatrix.h"

MyMatrix::MyMatrix()
{
}

MyMatrix::~MyMatrix()
{
}

MyMatrix::MyRow::MyRow()
{

}

MyMatrix::MyRow::MyRow(int dimension)
{
	Resize(dimension);
}

MyMatrix::MyRow::~MyRow()
{
}

void MyMatrix::MyRow::Resize(int dimension)
{
	vecData.resize(dimension);
}

float& MyMatrix::MyRow::operator[](int index)
{
	return vecData[index];
}

bool MyMatrix::Equal(float a, float b)
{
	if (a - EPSILON <= b && b - EPSILON <= a)
		return true;

	return false;
}

MyMatrix::MyMatrix(int dimension)
{
	Resize(dimension);
}

void MyMatrix::Print()
{
	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
			cout << (*this)[i][j] << ", ";

		cout << "\n";
	}
}

void MyMatrix::Resize(int dimension)
{
	vecData.resize(dimension);

	for (int i = 0; i < dimension; ++i)
		vecData[i].Resize(dimension);
}

int MyMatrix::Dimension()
{
	return vecData.size();
}

MyMatrix MyMatrix::Identity(int dimension)
{
	MyMatrix ret(dimension);

	for (int i = 0; i < dimension; ++i)
		for (int j = 0; j < dimension; ++j)
			ret[i][j] = (i == j ? 1.0f : 0.0f);


	return ret;
}

MyMatrix::MyRow& MyMatrix::operator[](int index)
{
	return vecData[index];
}

bool MyMatrix::operator==(MyMatrix& mat)
{
	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			if (!Equal((*this)[i][j], mat[i][j]))
				return false;
		}
	}

	return true;
}

bool MyMatrix::operator!=(MyMatrix & mat)
{
	return !((*this) == mat);
}

MyMatrix MyMatrix::operator+(MyMatrix & mat)
{
	MyMatrix ret(Dimension());

	for (int i = 0; i < Dimension(); ++i)
		for (int j = 0; j < Dimension(); ++j)
			ret[i][j] = (*this)[i][j] + mat[i][j];

	return ret;
}

MyMatrix MyMatrix::operator-(MyMatrix & mat)
{
	MyMatrix ret(Dimension());

	for (int i = 0; i < Dimension(); ++i)
		for (int j = 0; j < Dimension(); ++j)
			ret[i][j] = (*this)[i][j] - mat[i][j];

	return ret;
}

MyMatrix MyMatrix::operator*(MyMatrix & mat)
{
	MyMatrix ret(Dimension());

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			ret[i][j] = 0.0f;

			for (int k = 0; k < Dimension(); ++k)
				ret[i][j] += (*this)[i][k] * mat[k][j];
		}
	}

	return ret;
}

MyMatrix MyMatrix::operator*(float f)
{
	MyMatrix ret(Dimension());

	for (int i = 0; i < Dimension(); ++i)
		for (int j = 0; j < Dimension(); ++j)
			ret[i][j] = (*this)[i][j] * f;

	return ret;
}

MyMatrix MyMatrix::Inverse(float & determinant)
{
	MyMatrix ret = MyMatrix::Identity(Dimension());

	determinant = Determinant();

	if (Equal(determinant, 0.0f))
	{
		//cout << "역행렬이 존재하지 않음\n";
		return ret;
	}

	MyMatrix adj = Adjoint();
	ret = adj * (1 / determinant);
	return ret;
}

float MyMatrix::Determinant()
{
	if (Dimension() == 1)
		return (*this)[0][0];

	if (Dimension() == 2)
		return vecData[0][0] * vecData[1][1] - vecData[1][0] * vecData[0][1];

	float det = 0.0f;

	for (int i = 0; i < Dimension(); ++i)
		det += ((*this)[i][0] * Cofactor(i, 0));

	return det;
}

MyMatrix MyMatrix::Adjoint()
{
	MyMatrix ret(Dimension());

	for (int i = 0; i < Dimension(); ++i)
		for (int j = 0; j < Dimension(); ++j)
			ret[i][j] = Cofactor(j, i);

	return ret;
}

MyMatrix MyMatrix::Transpose()
{
	MyMatrix ret(Dimension());

	for (int i = 0; i < Dimension(); ++i)
		for (int j = 0; j < Dimension(); ++j)
			ret[i][j] = (*this)[j][i];

	return ret;
}

float MyMatrix::Cofactor(int row, int col)
{
	int nConst = 1;

	if ((row + col) % 2 != 0)
		nConst = -1;

	return nConst * Minor(row, col);
}

float MyMatrix::Minor(int row, int col)
{
	MyMatrix ret(Dimension() - 1);

	int minorRow = 0;
	int minorCol = 0;

	for (int i = 0; i < Dimension(); ++i)
	{
		if (row == i)
			continue;

		minorCol = 0;

		for (int j = 0; j < Dimension(); ++j)
		{
			if (col == j)
				continue;

			ret[minorRow][minorCol] = (*this)[i][j];
			++minorCol;
		}

		++minorRow;
	}

	return ret.Determinant();
}

MyMatrix MyMatrix::Translation(float x, float y, float z)
{
	MyMatrix ret = MyMatrix::Identity(4);
	
	ret[3][0] = x;
	ret[3][1] = y;
	ret[3][2] = z;

	return ret;
}

MyMatrix MyMatrix::Translation(MyVector3 & vec)
{
	MyMatrix ret = MyMatrix::Identity(4);

	ret[3][0] = vec.x;
	ret[3][1] = vec.y;
	ret[3][2] = vec.z;

	return ret;
}

MyMatrix MyMatrix::RotationX(float angle)
{
	MyMatrix ret = MyMatrix::Identity(4);

	ret[1][1] = cosf(angle);
	ret[1][2] = sinf(angle);
	ret[2][1] = -sinf(angle);
	ret[2][2] = cosf(angle);

	return ret;
}

MyMatrix MyMatrix::RotationY(float angle)
{
	MyMatrix ret = MyMatrix::Identity(4);

	ret[0][0] = cosf(angle);
	ret[0][2] = -sinf(angle);
	ret[2][0] = sinf(angle);
	ret[2][2] = cosf(angle);

	return ret;
}

MyMatrix MyMatrix::RotationZ(float angle)
{
	MyMatrix ret = MyMatrix::Identity(4);

	ret[0][10] = cosf(angle);
	ret[0][1] = sinf(angle);
	ret[1][10] = -sinf(angle);
	ret[21][21] = cosf(angle);

	return ret;
}

MyMatrix MyMatrix::View(MyVector3 & pos, MyVector3 & lookAt, MyVector3 & up)
{
	MyVector3 look = (lookAt - pos).Normalize();
	MyVector3 right = MyVector3::Cross(up, look).Normalize();
	MyVector3 newUp = MyVector3::Cross(look, right).Normalize();

	MyMatrix ret = MyMatrix::Identity(4);

	ret[0][0] = right.x;
	ret[0][1] = newUp.x;
	ret[0][2] = look.x;

	ret[1][0] = right.y;
	ret[1][1] = newUp.y;
	ret[1][2] = look.y;

	ret[2][0] = right.z;
	ret[2][1] = newUp.z;
	ret[2][2] = look.z;

	ret[3][0] = MyVector3::Dot(right, pos);
	ret[3][1] = MyVector3::Dot(newUp, pos);
	ret[3][2] = MyVector3::Dot(look, pos);

	return ret;
}

MyMatrix MyMatrix::Projection(float fovY, float aspect, float nearZ, float farZ)
{
	MyMatrix ret = MyMatrix::Identity(4);

	float scaleY = 1.0f / tanf(fovY / 2.0f);
	float scaleX = scaleY / aspect;

	ret[0][0] = scaleX;
	ret[1][1] = scaleY;
	ret[2][2] = farZ / (farZ - nearZ);
	ret[2][3] = 1.0f;
	ret[3][2] = -farZ * nearZ / (farZ - nearZ);
	ret[3][3] = 0.0f;

	return ret;
}

MyMatrix MyMatrix::Viewport(float x, float y, float w, float h, float minZ, float maxZ)
{
	MyMatrix ret = MyMatrix::Identity(4);

	ret[0][0] = w / 2.0f;
	ret[1][1] = -h / 2.0f;
	ret[2][2] = maxZ - minZ;

	ret[3][0] = x + w / 2.0f;
	ret[3][1] = y + h / 2.0f;
	ret[3][2] = minZ;

	return ret;
}
