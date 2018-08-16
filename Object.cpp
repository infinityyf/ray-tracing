#include "Object.h"
#include <vector>

//std::vector<Sphere> objects;
//记录所有生成的物体

Object::Object() {}

Object::~Object() {}

Sphere::Sphere() {}

Sphere::~Sphere() {}

ObjectList::ObjectList() {}

ObjectList::~ObjectList() {}

Object::Object(Vector3f v,Vector3f color, int material) {
	Point p(v.x, v.y, v.z);
	this->pos = p;
	this->pos_v = v;
	this->color = color;
	this->material = material;
}


Object::Object(Point p, Vector3f color, int material) {
	//此时需要拷贝
	Vector3f v(p.x, p.y, p.z);
	this->pos = p;
	this->pos_v = v;
	this->color = color;
	this->material = material;
}

Object::Object(double x, double y, double z, Vector3f color, int material) {
	Point p(x, y, z);
	this->pos = p;
	this->color = color;
	this->material = material;
}

int Object::GetMaterial()
{
	return this->material;
}


//调用父类的构造方法
Sphere::Sphere(Vector3f pos, double r, Vector3f color, int material) : Object(pos,color, material){
	this->radius = r;
}

Sphere::Sphere(Point p, double r, Vector3f color, int material) : Object(p,color, material) {
	this->radius = r;
}

Sphere::Sphere(double x, double y, double z, double r, Vector3f color, int material) : Object(x,y,z,color, material){
	this->radius = r;
}

Vector3f Sphere::GetNormal(Vector3f HitPoint)
{
	Vector3f normal = Vector3f(this->pos_v,HitPoint);
	normal.Normalize();
	return normal;
}

Vector3f Sphere::GetColor()
{
	Vector3f color = this->color;
	return color;
}


ObjectList* ObjectList::getInstance() {
	if (list == nullptr)list = new ObjectList();
	return list;
}

//先进行静态变量的初始化
ObjectList* ObjectList::list = new ObjectList();

void SetObject(Vector3f pos, double r,Vector3f color,int material) {
	ObjectList* spheres = ObjectList::getInstance();
	Sphere Sphere1(pos,r,color,material);
	//objects.push_back(Sphere1);
	spheres->objects.push_back(Sphere1);
}