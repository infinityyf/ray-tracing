#include "Object.h"
#include <vector>

//std::vector<Sphere> objects;
//��¼�������ɵ�����

Object::Object() {}

Object::~Object() {}

Sphere::Sphere() {}

Sphere::~Sphere() {}

ObjectList::ObjectList() {}

ObjectList::~ObjectList() {}

Object::Object(Vector3f v) {
	Point p(v.x, v.y, v.z);
	this->pos = p;
	this->pos_v = v;
}

Object::Object(Point p) {
	//��ʱ��Ҫ����
	Vector3f v(p.x, p.y, p.z);
	this->pos = p;
	this->pos_v = v;
}

Object::Object(double x, double y, double z) {
	Point p(x, y, z);
	this->pos = p;
}


//���ø���Ĺ��췽��
Sphere::Sphere(Vector3f pos, double r) : Object(pos){
	this->radius = r;
}

Sphere::Sphere(Point p, double r) : Object(p) {
	this->radius = r;
}

Sphere::Sphere(double x, double y, double z, double r) : Object(x,y,z){
	this->radius = r;
}

Vector3f Sphere::GetNormal(Vector3f HitPoint)
{
	Vector3f normal = Vector3f(this->pos_v,HitPoint);
	normal.Normalize();
	return normal;
}


ObjectList* ObjectList::getInstance() {
	if (list == nullptr)list = new ObjectList();
	return list;
}

//�Ƚ��о�̬�����ĳ�ʼ��
ObjectList* ObjectList::list = new ObjectList();

void SetObject(Vector3f pos, double r) {
	ObjectList* spheres = ObjectList::getInstance();
	Sphere Sphere1(pos,r);
	//objects.push_back(Sphere1);
	spheres->objects.push_back(Sphere1);
}