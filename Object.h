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



//这是一个单例模式哦
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
1. 如果子类没有定义构造方法，则调用父类的无参数的构造方法。

2. 如果子类定义了构造方法，不论是无参数还是带参数，在创建子类的对象的时候,首先执行父类无参数的构造方法，然后执行自己的构造方法。

3. 在创建子类对象时候，如果子类的构造函数没有显示调用父类的构造函数，则会调用父类的默认无参构造函数。

4. 在创建子类对象时候，如果子类的构造函数没有显示调用父类的构造函数且父类自己提供了无参构造函数，则会调用父类自己的无参构造函数。

5. 在创建子类对象时候，如果子类的构造函数没有显示调用父类的构造函数且父类只定义了自己的有参构造函数，则会出错（如果父类只有有参数的构造方法，则子类必须显示调用此带参构造方法）。

6. 如果子类调用父类带参数的构造方法，需要用初始化父类成员对象的方式

*/