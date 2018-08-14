#pragma once

#ifndef _RAY_H
#define _RAY_H
#include "math_tool.h"
#include "Camera.h"
#include <vector>
#include <map>

typedef struct {
	double t;
	Vector3f Hitpoint;
	Vector3f Normal;
	Vector3f Color;
	//����Ҫ������ɫ
}RayHit;

class Ray
{
public:
	Ray();
	~Ray();
	Ray(Vector3f origin,double x,double y, double z);//���������ϵ�һ����
	Vector3f origin;//Ĭ����ԭ�㣬Ӧ���������λ��
	Vector3f direction;
	Vector3f NormalDirection;
	std::vector<RayHit> HitPoints; //��¼���еĽ��������Ӧ�ķ���

	static void scanScreen(Camera& camera, Vector3f(*buffer)[WIN_WIDTH], int level);//������ᴫ���������͸��ͶӰ����ʵҲ���Բ����У�

	Vector3f GetPoint(double t);
	double HitSpheree(Vector3f center, double radius);
};



#endif // _RAY_H
