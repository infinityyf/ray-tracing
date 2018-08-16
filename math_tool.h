#pragma once
#ifndef _MATH_TOOL_H
#define _MATH_TOOL_H
class Point
{
public:
	Point();
	~Point();
	Point(double x, double y, double z);
	double x;
	double y;
	double z;
};




class Vector3f
{
public:
	Vector3f();
	~Vector3f();
	Vector3f(double x, double y, double z);
	Vector3f(Point begin, Point end);
	Vector3f(Vector3f begin, Vector3f end);
	Vector3f NumDot(double k);										//����
	void Normalize();												//��һ��
	static Vector3f Normalize(Vector3f v);
	static Vector3f CrossMult(Vector3f v1,Vector3f v2,int flag);	//���
	Vector3f operator+(const Vector3f& a);							//���ؼӷ�
	Vector3f operator-(const Vector3f& a);
	Vector3f operator*(const Vector3f& a);							//�˷�����ӦԪ�����
	double Mult(Vector3f v);										//���
	static double Distance(const Vector3f& v1,const Vector3f& v2);
	static double GetCosine( Vector3f& v1, Vector3f& v2);

	double x;
	double y;
	double z;
	
};



class Matrix
{
public:
	Matrix();
	~Matrix();
	Matrix mult(Matrix m);											//����˷�
	//Vector3f mult(Vector3f v);										//��������
	double m[4][4];
};




#endif