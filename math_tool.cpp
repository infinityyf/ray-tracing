
#include "math_tool.h"
#include <math.h>

Matrix::Matrix() {}
Matrix::~Matrix() {}
Vector3f::Vector3f() {}
Vector3f::~Vector3f() {}
Point::Point() {}
Point::~Point() {}

Point::Point(double x, double y, double z) {
	Point::x = x;
	Point::y = y;
	Point::z = z;
}

Vector3f::Vector3f(double x, double y, double z) {
	Vector3f::x = x;
	Vector3f::y = y;
	Vector3f::z = z;
}

Vector3f::Vector3f(Point begin, Point end) {
	Vector3f::x = end.x-begin.x;
	Vector3f::y = end.y-begin.y;
	Vector3f::z = end.z-begin.z;
}

Vector3f::Vector3f(Vector3f begin, Vector3f end) {
	Vector3f::x = end.x - begin.x;
	Vector3f::y = end.y - begin.y;
	Vector3f::z = end.z - begin.z;
}

Vector3f Vector3f::NumDot(double k) {
	Vector3f temp(k*this->x, k*this->y, k*this->z);
	/*this->x = k*this->x;
	this->y = k*this->y;
	this->z = k*this->z;*/
	return  temp;
}

void Vector3f::Normalize() {
	double Length = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	*this = this->NumDot(1/Length);
}

Vector3f Vector3f::Normalize(Vector3f v) {
	double Length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	Vector3f ret_v(v.x/Length, v.y / Length, v.z / Length);
	return ret_v;
}

Vector3f Vector3f::CrossMult(Vector3f v1, Vector3f v2,int flag)
{
	double _x = v1.y * v2.z - v1.z * v2.y;
	double _y = v1.z * v2.x - v1.x * v2.z;
	double _z = v1.x * v2.y - v1.y * v2.x;
	if (flag == 1) {
		double Length = sqrt(_x * _x + _y * _y + _z * _z);
		return Vector3f(_x / Length, _y / Length, _z / Length);
	}

	return Vector3f(_x, _y, _z);
}

Vector3f Vector3f::operator+(const Vector3f & a)
{
	Vector3f new_v(a.x + this->x, a.y + this->y, a.z + this->z);
	return new_v;
}

Vector3f Vector3f::operator-(const Vector3f & a)
{
	Vector3f new_v(this->x - a.x, this->y - a.y, this->z - a.z);
	return new_v;
}

Vector3f Vector3f::operator*(const Vector3f & a)
{
	Vector3f v = Vector3f(this->x*a.x,this->y*a.y,this->z*a.z);
	return v;
}

double Vector3f::Mult(Vector3f v)
{
	double _v;
	_v = x*v.x + y*v.y + z*v.z;
	return _v;
}

double Vector3f::Distance(const Vector3f & v1, const Vector3f & v2)
{
	double d = sqrt(pow(v1.x-v2.x,2)+ pow(v1.y - v2.y,2) + pow(v1.z - v2.z,2));
	return d;
}

double Vector3f::GetCosine(Vector3f & v1, Vector3f & v2)
{
	//这里默认都式单位向量
	double cos = Vector3f::Normalize(v1).Mult(Vector3f::Normalize(v2));
	return cos;
}


Matrix Matrix::mult(Matrix mat) {
	Matrix _m = Matrix();

	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			_m.m[i][j] = m[i][0] * mat.m[0][j] + m[i][1] * mat.m[1][j] + m[i][2] * mat.m[2][j] + m[i][3] * mat.m[3][j];
		}
	}
	return _m;
}

//Vector3f Matrix::mult(Vector3f v)
//{
//
//	Vector3f _v = Vector3f();
//	_v.x = v.x*m[0][0] + v.y*m[0][1] + v.z*m[0][2] + v.w*m[0][3];
//	_v.y = v.x*m[1][0] + v.y*m[1][1] + v.z*m[1][2] + v.w*m[1][3];
//	_v.z = v.x*m[2][0] + v.y*m[2][1] + v.z*m[2][2] + v.w*m[2][3];
//	_v.w = v.x*m[3][0] + v.y*m[3][1] + v.z*m[3][2] + v.w*m[3][3];
//	return _v;
//}
