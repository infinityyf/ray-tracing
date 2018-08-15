#pragma once

#ifndef _RAY_H
#define _RAY_H
#include "math_tool.h"
#include "Camera.h"
#include "LightPhysic.h"
#include "Object.h"
#include <vector>
#include <map>

typedef struct {
	double t;
	Vector3f Hitpoint;
	Vector3f Normal;
	Vector3f Color;
	//可能要加上颜色
}RayHit;

class Ray
{
public:
	Ray();
	~Ray();
	Ray(Vector3f origin,double x,double y, double z);//给出方向上的一个点
	Vector3f origin;//默认是原点，应该是摄像机位置
	Vector3f direction;
	Vector3f NormalDirection;
	std::vector<RayHit> HitPoints; //记录所有的交点和它对应的法线

	static void scanScreen(Camera& camera, Vector3f(*buffer)[WIN_WIDTH], int level);//在这里会传入相机进行透视投影（其实也可以不进行）
	static void scanScreen(Camera& camera, Vector3f(*buffer)[WIN_WIDTH], int level, EnvironmentLight& light0, PointLight& light1);
	Vector3f GetPoint(double t);
	double HitSpheree(Vector3f center, double radius);

	bool HidePointLight(std::vector<Sphere>& objects);
	//在点光源下是否被遮蔽
	static Vector3f Tracing(const Vector3f& hitpoint,const Vector3f& normal);

};



#endif // _RAY_H
