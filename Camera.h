#pragma once


#ifndef _CAMERA_H
#define _CAMERA_H
#include "math_tool.h"
#include "Screen.h"

//每个像素的采样数
#define ONE_SAMPLE		1
#define THREE_SAMPLE	3
#define FOUR_SAMPLE		4

class Camera
{
public:
	Camera();
	~Camera();
	Camera(Point pos);
	void lookat(double tarx, double tary, double tarz, double headx, double heady, double headz);
	Point CameraPosition;
	Vector3f Postion4Calcu;
	Vector3f N;//view_z
	Vector3f V;//view_x
	Vector3f U;//view_y

	void SetProjection(double near,double far,double width_left,double width_right,double height_top,double height_buttom);

	//计算每个像素的坐标，传入一个指针数组
	void GetPixelPos(int level);


	//默认尺度
	double D = 300;
	double F = 900;
	double width_left = -300;//x
	double width_right = 300;
	double height_top = 300;//y
	double height_buttom = -300;

	//记录每条射线通过的像素的坐标目前是一个像素一条射线
	Vector3f PixelPos[WIN_HIGH][WIN_WIDTH];

	//--------|---------0--------|
	//	300	  |---300---0---300--|

};


#endif