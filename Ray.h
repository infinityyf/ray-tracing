#pragma once

#ifndef _RAY_H
#define _RAY_H
#include "math_tool.h"
#include "Camera.h"
#include "LightPhysic.h"
#include "Object.h"
#include <vector>
#include <map>

#define TRACING_MAX 4
//�������׷�ٵ����ݹ����

#define LAMBERT_FADE 0.01 
#define PHONG_FADE   0.09
#define MIRROR_FADE  0.3

typedef struct {
	double t;
	Vector3f Hitpoint;
	Vector3f Normal;
	Vector3f Color;
	int material;
	//����Ҫ������ɫ
}RayHit;

class Ray
{
public:
	Ray();
	~Ray();
	Ray(Vector3f origin,double x,double y, double z);//���������ϵ�һ����
	Ray(Vector3f origin,Vector3f dir);//ֻ��������
	Vector3f origin;//Ĭ����ԭ�㣬Ӧ���������λ��
	Vector3f direction;
	Vector3f NormalDirection;                
	std::vector<RayHit> HitPoints; //��¼���еĽ��������Ӧ�ķ���

	static void scanScreen(Camera& camera, Vector3f(*buffer)[WIN_WIDTH], int level);//������ᴫ���������͸��ͶӰ����ʵҲ���Բ����У�
	static void scanScreen(Camera& camera, Vector3f(*buffer)[WIN_WIDTH], int level, 
		EnvironmentLight& light0, 
		PointLight& light1,
		DirectLight& light2);
	Vector3f GetPoint(double t);
	double HitSpheree(Vector3f center, double radius);

	bool HidePointLight(std::vector<Sphere>& objects);
	//�ڵ��Դ���Ƿ��ڱ�
	Vector3f Tracing(Vector3f& hitpoint,
		Vector3f& normal, 
		std::vector<Sphere>& objects,
		int count,
		EnvironmentLight& light0,
		PointLight& light1,
		DirectLight& light2);

};



#endif // _RAY_H
