#pragma once

#ifndef _OBJECT_H
#define _OBJECT_H

#include "math_tool.h"
#include <vector>


class Object
{
public:
	Object();
	~Object();
	Object(Vector3f pos);
	Object(Point p);
	Object(double x, double y, double z);
	Point pos;
	Vector3f pos_v;
};



class Sphere : public Object
{
public:
	Sphere();
	~Sphere();
	Sphere(Vector3f pos,double r);
	Sphere(Point p, double r);
	Sphere(double x, double y, double z, double r);
	Vector3f GetNormal(Vector3f HitPoint);
	double radius;
};

void SetObject(Vector3f pos, double r);



//����һ������ģʽŶ
class ObjectList
{
public:
	std::vector<Sphere> objects;
	static ObjectList* getInstance();

private:
	static ObjectList* list;
	ObjectList();
	~ObjectList();
	

};




#endif


/*
1. �������û�ж��幹�췽��������ø�����޲����Ĺ��췽����

2. ������ඨ���˹��췽�����������޲������Ǵ��������ڴ�������Ķ����ʱ��,����ִ�и����޲����Ĺ��췽����Ȼ��ִ���Լ��Ĺ��췽����

3. �ڴ����������ʱ���������Ĺ��캯��û����ʾ���ø���Ĺ��캯���������ø����Ĭ���޲ι��캯����

4. �ڴ����������ʱ���������Ĺ��캯��û����ʾ���ø���Ĺ��캯���Ҹ����Լ��ṩ���޲ι��캯���������ø����Լ����޲ι��캯����

5. �ڴ����������ʱ���������Ĺ��캯��û����ʾ���ø���Ĺ��캯���Ҹ���ֻ�������Լ����вι��캯�����������������ֻ���в����Ĺ��췽���������������ʾ���ô˴��ι��췽������

6. ���������ø���������Ĺ��췽������Ҫ�ó�ʼ�������Ա����ķ�ʽ

*/