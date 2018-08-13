#pragma once

#ifndef _RAY_H
#define _RAY_H
#include "math_tool.h"
#include "Camera.h"
class Ray
{
public:
	Ray();
	~Ray();
	Ray(Vector3f origin,double x,double y, double z);//给出方向上的一个点
	Vector3f origin;//默认是原点，应该是摄像机位置
	Vector3f direction;
	Vector3f NormalDirection;


	static void scanScreen(Camera& camera, Vector3f(*buffer)[WIN_WIDTH]);//在这里会传入相机进行透视投影（其实也可以不进行）

	Vector3f GetPoint(double t);
	double HitSpheree(Vector3f center, double radius);
};



#endif // _RAY_H
